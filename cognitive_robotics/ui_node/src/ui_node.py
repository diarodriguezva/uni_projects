#!/usr/bin/env python

import roslib; roslib.load_manifest('ui_node')
import rospy

from ai_node.srv import *
from rosgraph_msgs.msg import Log

from gevent.wsgi import WSGIServer
from gevent import monkey; monkey.patch_all()

import sys, errno

from flask import Flask, render_template, request, jsonify
import json
app = Flask(__name__)

SERVICE = {
    "/input_cmd" : InputCmd,
    "/gripper_control/open_gripper" : OpenGripper,
    "/gripper_control/close_gripper" : CloseGripper,
    "/world/detect_objects" : found_objects,
    "/rosout_service" : InputCmd,
    "/gripperbot_control/print_gripper_pose" : PrintGripperPose
}

open_services = {}

##### ROUTES HERE #####

def call_service(service, data=None):

    response = None
    
    # Open a new service if it isn't already in the open services list.
    try:
        if not service in open_services:
            srv = rospy.ServiceProxy(service, SERVICE[service], persistent=False)
            open_services[service] = srv
        if data:
            response = open_services[service](data)
        else:
            response = open_services[service]()
    
    except:
        e = sys.exc_info()[0]
        ex = "Service call failed to {0}".format(service);
        rospy.logerr(ex)
    
    return response

@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/gripper-pose', methods=["GET"])
def get_gripper_pose():

    response = call_service("/gripperbot_control/print_gripper_pose")
    retval = []
    if response:
        retval.append(response.x)
        retval.append(response.y)
        retval.append(response.z)

    return jsonify({"data": retval})

@app.route('/input-xml', methods=["POST"])
def xml_input():
    xml = request.form.get('xml')

    call_service("/input_cmd", xml)

    return jsonify({"data": "success: sent the xml command to AI!"})

@app.route('/gripper-coordinates', methods=["POST"])
def gripper_coordinates():
    coord = request.form.get('cmd')
    
    c = coord.strip().split(" ")
    
    if len(c) < 3:
        rospy.loginfo("Error: Three coordinates required. Separate them with space.")
        return jsonify({"status": "error"})
    
    tag = "<coordinates x='" + c[0] + "' y='" + c[1] + "' z='" + c[2] + "' />"
    xml = "<instructions><move><tolocation>" + tag + "</tolocation></move></instructions>"

    #print xml

    call_service("/input_cmd", xml)

    return jsonify({"data": "success: sent the move_coordinates command to AI!"})

@app.route('/gripper-grasp', methods=["POST"])
def gripper_grasp():
    cmd = request.form.get('cmd')
    # print cmd

    if cmd == "gripper-open":
        rospy.loginfo("Opening the gripper.")
        call_service("/gripper_control/open_gripper")

    elif cmd == "gripper-close":
        rospy.loginfo("Closing the gripper.")
        call_service("/gripper_control/close_gripper")
    
    return jsonify({"data": "suuupeer success!"})

@app.route('/gripper-move', methods=["POST"])
def gripper_move():
    color = request.form.get('cmd')

    if color in ["red", "green", "yellow"]:
        rospy.loginfo("Trying to move the gripper above the " + color + " ball.")
        xml = "<instructions><move><obj><type shape='sphere' color='" + color + "'/></obj></move></instructions>"

        call_service("/input_cmd", xml)

    return jsonify({"data": "suuupeer success!"})

@app.route('/get-objects', methods=["GET"])
def get_objects():
    """ This view fetches the objects from the camera node and shows them to the user. """

    response = call_service("/world/detect_objects")
    ret = []

    if response:
        for idx, name in enumerate(response.name):
            if name:
                item = {}
                item["color"] = name
                location = []
                location = [response.x[idx], response.y[idx], response.z[idx]]
                item["location"] = location
                ret.append(item)
    else:
        return json.dumps([{"status" : "error"}])

    return json.dumps(ret)

@app.route('/rosout', methods=["GET"])
def poll_rosout():
    try:
        data = call_service("/rosout_service", "test")
        if data.str:
            return jsonify({"data": data.str})
    except:
        pass
    
    return jsonify({"data": ""})

##### EXECUTE #####

if __name__ == '__main__':
    #app.run(debug=True, threaded=True)
    http_server = WSGIServer(('', 5000), app)
    http_server.serve_forever()
