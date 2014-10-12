#!/usr/bin/env python
import rospy
import zmq
from gripper_control_srvs.srv import *

def handle_open_gripper(req):
    res = OpenGripperResponse()
    socket.send("open")
    status = socket.recv()
    if status == "ok":
        res.success = True
    else:
        res.success = False
    print "open gripper: " + status
    return res

def handle_close_gripper(req):
    res = CloseGripperResponse()
    socket.send("close")
    status = socket.recv()
    if status == "ok":
        res.success = True
    else:
        res.success = False
    print "close gripper: " + status
    return res

def gripper_server():
    rospy.init_node('gripper_control')
    rospy.Service('/gripper_control/open_gripper', OpenGripper, handle_open_gripper)
    rospy.Service('/gripper_control/close_gripper', CloseGripper, handle_close_gripper)
    rospy.spin()

def usage():
    return "%s [host]"%sys.argv[0]

if __name__ == "__main__":

    if len(sys.argv) > 1:
        host = sys.argv[1]
    else:
        print usage()
        sys.exit(1)

    port = 6666
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://%s:%s" % (host, port))
    gripper_server()

