#!/usr/bin/env python
#__author__ = 'Peter, Raphael'
import roslib
roslib.load_manifest('ai_node')
import rospy
#import tf

import StringIO # testing

from ai_node.srv import InputCmd
from std_msgs.msg import String

from rosgraph_msgs.msg import Log # for rosout

from xml.dom import minidom, Node
import tasks

class AI(object):
    ''' The AI class works as a container for the ROS service handlers. It
        also parses and executes the tasks given as user input. '''

    def __init__(self, input):
        # initialize the ROS service and listeners here
        # communications

        rospy.init_node('ai_node')
        
        rospy.Service('input_cmd', InputCmd, self.input_cmd_cb)
        
        self.msgs = []
        rospy.Subscriber("/rosout", Log, self.update_rosout, queue_size=1) # for rosout
        rospy.Service('rosout_service', InputCmd, self.rosout_srv_cb) # for rosout service

        rospy.loginfo( "ai_node is now initialized.")
        rospy.spin()
        
    def update_rosout(self, data):
        
        msg_header = ""
        msg_sender = "[" + data.name + "] "

        if data.level == 5:
            msg_header = "[FATAL] "
        elif data.level == 4 or data.level == 8:
            msg_header = "[ERROR] "
        elif data.level == 3:
            msg_header = "[WARN] "
        elif data.level == 2:
            msg_header = "[INFO] "
        elif data.level == 1:
            msg_header = "[DEBUG] "
            
        msg = msg_header + msg_sender + data.msg
        self.msgs.append(msg)
       
    def run(self):
        # call the parser and parse the files, return a 'stack' of objects
        instructions = self.parser.parse()

        # loop through the atomic instructions and execute them
        for instruction in instructions:
            instruction.run()

    def input_cmd_cb(self, xml):
        rospy.loginfo("AI node received XML instructions.")

        self.parser = Parser(xml)
        self.run()

        return "success: True"
    
    def rosout_srv_cb(self, data):
        if (self.msgs):
            s = self.msgs.pop(0) #pop the first item
            return s
        return ""

class Parser:
    ''' The Parser class parses the instructions xml file given as user input
        and returns a stack of initialized Task objects, which are then used
        in the AI class to run the atomic tasks. '''

    #xmldoc = minidom.parse('src/input.xml')

    def __init__(self, xml):
        self.xmldoc = minidom.parseString(xml.str)
        #self.xmldoc = minidom.parse('src/input.xml')
        rospy.loginfo( "Parsed XML successfully.")

    def parse(self):
        # parse the xml and initialize the required tasks to a list
        itemlist = self.xmldoc.getElementsByTagName('instructions')[0]
        tasks_list = []

        for instr in itemlist.childNodes:
            if instr.nodeType == Node.ELEMENT_NODE:
                if instr.nodeName == 'sort':
                    new = tasks.Sort(instr)
                elif instr.nodeName == 'move':
                    new = tasks.Move(instr)
                tasks_list.append(new)

        #for t in tasks_list: print t
        return tasks_list

if __name__ == '__main__':
    ai_node = AI("dummy data")
