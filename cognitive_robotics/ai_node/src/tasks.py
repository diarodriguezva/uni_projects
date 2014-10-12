#!/usr/bin/env python
from ai import *
from time import sleep
import math
#from robot_control.srv import MoveToCS, MoveToOS, MoveJoints, PrintGripperPose
from ai_node.srv import found_objects, OpenGripper, CloseGripper, MoveToCS, MoveToOS, inspect_objects

''' This file contains the atomic instructions for different robot tasks as
    separate class files. '''

STATIC_LOC = [0.4935540556907654, 0.058287959545850754, 0.22839400172233582]
STD_GRIPPER = [0.394441157579, 0.00578322215006, 0.428783506155]

TO_YELLOW_J = [-2.05, 0.45, 0.5]
TO_YELLOW_OS = [-0.229625120759, -0.429400056601, 0.243648022413]

TO_RED_J = [-2.2, 0.0, 0.65]
TO_RED_OS = [-0.230930104852, -0.310132682323, 0.247499778867]

TO_GREEN_J = [-2.45, -0.35, 0.60]
TO_GREEN_OS = [-0.241928890347, -0.209063321352, 0.237882196903]

ABSTELLGLEIS = [0, 0.4, 0.259]

OPEN_GRIPPER = 0
CLOSE_GRIPPER = 1

MOVE_CS = 0
MOVE_OS = 1

SAFE_HIGHT = 0.31
SAFE_HIGHT_FROM = 0.428783506155

WORKSPACE_HEIGHT = 0.27

ANGLE_THRESHOLD = math.radians(12)

class Task():

    def __init__(self, AI, instr):
        self.instr = instr

    def grip(self, cmd):
        """
            Open and close the gripper.
            @param cmd: OPEN_GRIPPER or CLOSE_GRIPPER
        """
        response = False

        if cmd == OPEN_GRIPPER:
            try:
                service = rospy.ServiceProxy('/gripper_control/open_gripper', OpenGripper)
                response = service()
                rospy.loginfo("Opened the gripper.")
            except rospy.ServiceException, e:
                ex = "ERROR: Could not connect to the service: " + str(e)
                rospy.logerr(ex)


        elif cmd == CLOSE_GRIPPER:
            try:
                service = rospy.ServiceProxy('/gripper_control/close_gripper', CloseGripper)
                response = service()
                rospy.loginfo("Closed the gripper.")
            except rospy.ServiceException, e:
                ex = "ERROR: Could not connect to the service: " + str(e)
                rospy.logerr(ex)
    
        if response:
            return True

        return False

    def find_object(self, item):
        """ Find a single item given as parameter and retur n coordinates or False """
        try:
            #service = rospy.ServiceProxy('/world/detect_objects', found_objects)
            service = rospy.ServiceProxy('/world/found_objects', found_objects)
            response = service()
        except rospy.ServiceException, e:
            ex = "ERROR: Could not connect to the service: " + str(e)
            rospy.logerr(ex)
            return False

        location = False
        #other balls in scene
        self.otherObj = []
        self.otherName = []
        
        if not item['shape'] == 'bin':
            for idx,name in enumerate(response.name):
                #only search the objects and not the bins
                if item['color'] == name:
                    location = []
                    location = [response.x[idx], response.y[idx], response.z[idx]]
                else:
                    if response.x[idx] != 0:
                        #array: [[obj1x, obj1y],[obj2x, obj2y] ]
                        self.otherObj.append([response.x[idx], response.y[idx], response.z[idx]] )
                        self.otherName.append(response.name[idx])
        else:
            if item['color'] == 'green':
                location = TO_GREEN_OS
            if item['color'] == 'red':
                location = TO_RED_OS
            if item['color'] == 'yellow':
                location = TO_YELLOW_OS

        if location:
            rospy.loginfo("Found position: " + str(location))

        if location:
            for number in location:
                if math.isnan(number):
                    return False

        return location

    def check_object_collision(self, objTarget):
        collision = False
        obstacles = self.otherObj
        self.obstacle = []
        goal = objTarget[0]

        qGoal = math.atan2(goal[1], goal[0])

        for obstacle in obstacles:
            qObst = math.atan2(obstacle[1], obstacle[0])

            goalX = goal[0] / math.cos(qGoal)
            obstX = obstacle[0] / math.cos(qObst)
            rospy.loginfo("Angle btwn objects: " + str(math.degrees( math.fabs(qGoal - qObst) )) + " DEG" )

            if ( obstX ) < goalX and math.fabs(qGoal - qObst) < ANGLE_THRESHOLD:
                collision = True    
                self.obstacle = obstacle
                self.otherObj.remove(obstacle)
                break
        return collision


    def move_gripper(self, MODE, location):
        """
            Moves the gripper to the given location.
        """
        response = False        
        try:
            if MODE == MOVE_CS:
                service = rospy.ServiceProxy('/gripperbot_control/move_to_cs', MoveToCS)
            elif MODE == MOVE_OS:
                service = rospy.ServiceProxy('/gripperbot_control/move_to_os', MoveToOS)
            response = service('gripper', location[0], location[1], location[2])
        except rospy.ServiceException, e:
            ex = "ERROR: Could not connect to the service: " + str(e)
            rospy.logerr(ex)
        

        if not response.success:
            rospy.logerr("Gripperbot failed, Object out of reach.")
            rospy.logerr(response)

        if response:
            return response.success
        else:
            return False

    def move_object(self, from_loc, to_loc):
        """
            Moves an object from location from_loc to location to_loc.
        """
        rospy.loginfo("moving from " + str(from_loc) + " to " + str(to_loc))
        q1 = math.atan2(from_loc[1], from_loc[0])
        x_offset = 0.02 * math.cos(q1)
        y_offset = 0.02 * math.sin(q1)

        from_loc[2] = WORKSPACE_HEIGHT
        from_loc[1] = 1.1267 * from_loc[1] + 0.0223

        from_loc[0] = from_loc[0] + x_offset
        from_loc[1] = from_loc[1] + y_offset

        safe_from_loc = list(from_loc)
        safe_to_loc = list(to_loc)

        safe_from_loc[2] = SAFE_HIGHT
        safe_to_loc[2] = SAFE_HIGHT_FROM

        if not self.move_gripper(MOVE_CS, STD_GRIPPER):
            return False
        if not self.grip(OPEN_GRIPPER):
            return False
        if not self.move_gripper(MOVE_CS, safe_from_loc):
            return False
        #   return True
        rospy.logwarn("Not in science-mode, real behavior. Be careful, this thing doesn't drive itself!")

        if not self.move_gripper(MOVE_OS, from_loc):
            return False
        if not self.grip(CLOSE_GRIPPER):
            return False
        if not self.move_gripper(MOVE_CS, safe_from_loc):
            return False
         
        if not self.move_gripper(MOVE_CS, STD_GRIPPER):
            return False

        if not self.move_gripper(MOVE_CS, safe_to_loc):
            return False

        if not self.move_gripper(MOVE_CS, to_loc):
            return False
        if not self.grip(OPEN_GRIPPER):
            return False
        if not self.move_gripper(MOVE_CS, safe_to_loc):
            return False
        if not self.move_gripper(MOVE_CS, STD_GRIPPER):
            return False

        return True

    def move_to_pos(self, position, safe):
        """
            Moves to a position.
        """
        if safe:
            rospy.loginfo("Entering safe mode (Safe Z-axis).")

        safe_position = list(position)

        safe_position[2] = SAFE_HIGHT

        if position[2] < WORKSPACE_HEIGHT:
            position[2] = WORKSPACE_HEIGHT          

        rospy.loginfo("moving to " + str(position))

        if not self.move_gripper(MOVE_CS, position):
            return False

        if not safe:    
            if not self.move_gripper(MOVE_CS, safe_position):
                return False
            if not self.move_gripper(MOVE_OS, position):
                return False

        return True


    def inspect_workspace(self):
        rospy.loginfo("Moving gripper to std position and inspecting workspace...")
        if not self.move_gripper(MOVE_CS, STD_GRIPPER):
            return False
        try:
            service = rospy.ServiceProxy('/world/inspect_workspace', inspect_objects)
            response = service()
            if response:
                print str(response)
        except rospy.ServiceException, e:
            ex = "ERROR: Could not connect to the service: " + str(e)
            rospy.logerr(ex)



class Move(Task):
    ''' Move the specified objects to the given location. '''
    def __init__(self, instr):        

        # Initialize different moving actions available
        # These are chosen according to the parsed DOM

        self.coordinates = [0.0, 0.0, 0.0]

        MOVE_ACTIONS = {
            "object" : self.move_by_object,
            "coordinates" : self.move_by_coordinates
        }

        self.action = None  # Set it to None until an action is chosen
        
        # If any <obj> elements are found, set the action to move_by_type
        obj = instr.getElementsByTagName('obj')
        if obj:
            types = obj[0].getElementsByTagName('type')
            self.action = MOVE_ACTIONS["object"]    # set the action type to be 'move_by_object

            self.objList = []
            self.locDict = {}

            

            for type in types:
                self.objList.append({'shape': type.getAttribute('shape'), 'color': type.getAttribute('color')})
        # <tolocation> tags
        toloc = instr.getElementsByTagName('tolocation')
        if toloc:
            
            # move to location either by <type> ...
            loc = toloc[0].getElementsByTagName('type')
            if loc:
                self.locDict['shape'] = loc[0].getAttribute('shape')
                self.locDict['color'] = loc[0].getAttribute('color')
            
            # ... or give coordinates <coordinates>
            coord = toloc[0].getElementsByTagName('coordinates')
            if coord:
                self.coordinates[0] = float(coord[0].getAttribute('x'))
                self.coordinates[1] = float(coord[0].getAttribute('y'))
                self.coordinates[2] = float(coord[0].getAttribute('z'))
                self.action = MOVE_ACTIONS["coordinates"]   # set the action type to move to coordinates
    
    def __str__(self):
        #return ">move: " + str(self.objList) + " to " + str(self.locDict)
        return ">> move: moving to location."
    
    def move_by_object(self):

        rospy.loginfo("Moving the gripper according to given objects list.")

        MOVE_ONCE = False
        from_loc = []
        to_loc = from_tmp = False

        #if there is no to location, just move to the object
        if len(self.locDict) == 0:
            MOVE_ONCE = True

        if not MOVE_ONCE:
            self.inspect_workspace()

        timeCounter = 0
        for obj in self.objList:
            while from_tmp == False and timeCounter < 5:
                rospy.loginfo("Waiting for TARGET position...")
                from_tmp = self.find_object(obj)
                sleep(1)
                timeCounter += 1
            from_loc.append(from_tmp)

        #TODO do timeout here
        timeCount = 0
        while self.check_object_collision(from_loc) and timeCount < 3:
            #blocking obstacle
            rospy.logwarn("COLLISION DETECTED")
            rospy.loginfo("Starting collision avoidance....")
            timeCount += 1

            if not self.move_object(self.obstacle, ABSTELLGLEIS):
                rospy.logwarn ("Could not move obstacle")
                return False
            self.obstacle = []
        rospy.loginfo("No collision detected.")

        if not MOVE_ONCE:
            timeCounter = 0    
            while to_loc == False and timeCounter < 5:
                rospy.loginfo("Waiting for GOAL position...")
                to_loc = self.find_object(self.locDict)
                sleep(1)
                timeCounter += 1
    
        if MOVE_ONCE and from_loc[0]:
            if not self.move_to_pos(from_loc[0], False):
                rospy.logerr("Moving aborted, object probably not in workspace (according to gripper).")
                return False
            else:
                return True

        for from_l in from_loc:
            if from_l and to_loc:
                if not self.move_object(from_l, to_loc):
                    rospy.logerr ("Moving aborted, object probably not in workspace (according to gripper).")
                    return False
            else:
                rospy.logerr("One of the positions or both are not recognized")
                return False

        rospy.loginfo("Successfully moved an object.")

        return True
    
    def move_by_coordinates(self):
        rospy.loginfo("Moving gripper to given coordinates.")
        self.move_to_pos(self.coordinates, True)

    def run(self):
        self.action()

