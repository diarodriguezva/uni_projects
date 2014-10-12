#!/usr/bin/env python
import roslib
roslib.load_manifest('ball_detection2')
import sys
import rospy
import numpy as np
import pickle
import tf
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from find_balls import *
from ball import *
from matplotlib import pyplot as plt

NUMBER_BALLS = 3
ballnames = ["green", "red", "yellow"]
balls=[ball(name) for name in ballnames]


### TODO load histograms only once
### TODO shrink image for calulations? image pyramid?
### TODO learn/refine histogram from last frame detection? (detect bad history refinement e.g. through occlusions)


def getHistParams():
    CHANNELS = [0, 1]
    RANGES = [0, 256, 0, 256]
    BUCKETS = [30, 10]
    return CHANNELS, RANGES, BUCKETS


def generateContours(probabilityMap):
    upper_threshold = max(np.max(probabilityMap) * 0.90,50)

    ret, mask_strong = cv2.threshold(probabilityMap, upper_threshold, 255, cv2.THRESH_BINARY)
    ret, mask_weak = cv2.threshold(probabilityMap, 1, 255, cv2.THRESH_BINARY)
    # mask_strong_1, mask_weak_1 = np.array(mask_strong), np.array(mask_weak)  #copy because findContours destroys input
    contours_strong, hierarchy = cv2.findContours(mask_strong, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    contours_weak, hierarchy = cv2.findContours(mask_weak, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    testpoints = []
    for contour in contours_strong:
        testpoints.append(tuple(contour[0][0]))

    hulls = []
    maxHullPoints = 0
    for contour in contours_weak:
        hull = cv2.convexHull(contour)
        hulls.append(hull)
        maxHullPoints = max(maxHullPoints, len(hull))

    finalContours = []
    for i, contour in enumerate(contours_weak):
        hull = hulls[i]
        # if cv2.contourArea(contour)/cv2.contourArea(hull)<0.85:
        #      continue
        #print cv2.arcLength(hull,True)/cv2.arcLength(contour,True), cv2.contourArea(contour)/cv2.contourArea(hull)
        # print cv2.arcLength(hull,True),cv2.arcLength(contour,True), cv2.contourArea(contour),cv2.contourArea(hull),len(hull), len(contour)
        # #TODO add prior knowledge tests for length and area
        # len_hull = len(hull)
        # if len_hull < 0.001*len(contour)<10:
        #     continue
        # for i in range(len_hull):
        #     sample=hull[i-5,i,i+5]
        #     angle=calculateAngle(sample)

        if cv2.arcLength(hull,True)<200:
            continue
        for testpoint in testpoints:
            if cv2.pointPolygonTest(contour, testpoint, False) >= 0:
                finalContours.append(hull)

    print "finalContours generated"
    return finalContours

class image_converter:
    def __init__(self):
        global br
        cv2.namedWindow("Image window", 1)
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/gscam/image_raw", Image, self.callback,queue_size=1)
        br = tf.TransformBroadcaster()

    def calc3D(self, radius, x2, y2):
        #Camera parameters
        realDiameter = 0.069  #0.066#m
        focalDistance = 1310.2  #1308.0*1.15#px
        X_AXIS_CAMERA = 645.3  #655.0#px
        Y_AXIS_CAMERA = 306.3  #329.0#px
        #calculations
        z = realDiameter * focalDistance / (2.0 * float(radius))  # + 35
        factor = z / focalDistance
        x = (float(x2) - X_AXIS_CAMERA) * factor
        y = (float(y2) - Y_AXIS_CAMERA) * factor
        return x, y, z

    def callback(self, image_msg):
        print "image recieved"
        center = None

        try:
            shape = (image_msg.height, image_msg.width, 3)
            np_arr = np.fromstring(image_msg.data, np.uint8)
            frame = np_arr.reshape(shape)
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        except CvBridgeError, e:
            print e
        print "image converted"
        # cv2.imwrite("balls.png", frame)
        img_foundballs=np.copy(frame)
        cv2.imwrite("balls.png",frame)

        ## Preprocessing
        kernel = cv2.getGaussianKernel(6, 2)
        frame = cv2.sepFilter2D(frame, -1, kernel, kernel.T)
        ## Color Conversion
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        print "preprocessing done"

        for currentBall in balls:
            print "searching for " + currentBall.color + " ball"

            CHANNELS, RANGES, BUCKETS = getHistParams()
            probabilityMap = matchHistogram(CHANNELS, RANGES, hsv, currentBall.histogram)
            print "backprojection done"

            ##Morphology
            kernel = cv2.getGaussianKernel(12, 4) #TODO cheaper filter
            probabilityMap=cv2.sepFilter2D(probabilityMap, -1, kernel, kernel.T )

            contours = generateContours(probabilityMap)
            inlierFractions=[]
            for cnt in contours:
                # pointsDeleted=True
                pointsDeleted=False
                while pointsDeleted:
                    pointsDeleted=False
                    for i in range(len(cnt)-2):
                        a= np.array(cnt[i-1][0])
                        b=np.array(cnt[i][0])
                        c=np.array(cnt[i+1][0])
                        u = b-a
                        v = c-b
                        c = np.dot(u,v)/np.linalg.norm(u)/np.linalg.norm(v) # -> cosine of the angle
                        angle=np.arccos(c)
                        radius = np.linalg.norm(np.array(cnt[i-1][0]) - np.array(cnt[i+1][0]))/(2*np.sin(angle))
                        #angle_deg = 180-angle/np.pi*180

                        #print radius
                        if 100>radius>400:
                            np.delete(cnt,i)
                            pointsDeleted=True

                # c, r, inlierFraction = fitCircle(cnt)
                # inlierFractions.append(inlierFraction)

            # maxInlierFraction=max(inlierFractions)
            # for i,cnt in enumerate(contours):
            #     if inlierFractions[i]==maxInlierFraction:
            #         finalContour=cnt
            # for i,cnt in enumerate(contours):
            #     if inlierFractions[i]>=0.8*maxInlierFraction:
            #         finalContour=np.concatenate((finalContour,cnt))
            if len(contours)>=1:
                finalContour=np.concatenate(contours)
                # for point in finalContour:
                #     point=tuple(point[0])
                #     cv2.circle(img_foundballs,point,2,(255,i*2550/len(finalContour)/10,0),-1)
                #     i=i+1
                i=0
                for point in finalContour:
                    point=tuple(point[0])
                    cv2.circle(img_foundballs,point,2,(255,i*2550/len(finalContour)/10,0),-1)
                    i=i+1

                finalCenter, finalRadius, tmp = fitCircle(finalContour)
                x=finalContour[:,0,0]
                y=finalContour[:,0,1]
                finalCenter, finalRadius, tmp=optimizeCircle(finalCenter,x,y)
                if tmp<400:
                    print "circle found"
                    print finalCenter, finalRadius
                    i=0
                #     #r,x,y=currentBall.filter2D(finalRadius,finalCenter[0],finalCenter[1])
                    r,x,y=finalRadius,finalCenter[0],finalCenter[1]
                    cv2.circle(img_foundballs, (int(x),int(y)), int(r), (0, 0, 255), 1)

                    ##Calculate 3D position
                    x3,y3,z3=0,0,0
                    if r>0:
                        x3, y3, z3 = self.calc3D(r, x, y)
                    print "3D position calculated"
                    x3+=0.03
                    z3+=0.09

                    br.sendTransform(
                        (x3, y3, z3), tf.transformations.quaternion_from_euler(0, 0, 0),
                        rospy.Time.now(), "tf_" + currentBall.color + "_start", "cam_effector_2")
                    print x3, y3, z3
                else:
                    br.sendTransform(
                        (0.03, 0, 0.09), tf.transformations.quaternion_from_euler(0, 0, 0),
                        rospy.Time.now(), "tf_" + currentBall.color + "_start", "cam_effector_2")


        cv2.imshow("foundballs", img_foundballs)
        cv2.waitKey(1)

def main(args):
    ic = image_converter()
    rospy.init_node('ball_detection2',anonymous=True)
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print "Shutting down"
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main(sys.argv)

