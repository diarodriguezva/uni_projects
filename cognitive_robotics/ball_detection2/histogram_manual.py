__author__ = 'student'
import cv2
import numpy as np
from detector_node import getHistParams
import pickle

def draw_mask(event,x,y,flags,param):
    global frame,drawing,img,mask
    samplesize = 100
    if (event == cv2.EVENT_LBUTTONDOWN):
        img = np.copy(frame)
        w,h,c=img.shape
        mask = np.zeros((w,h,1),np.uint8)
        drawing = True
        point = (x, y)
        cv2.circle(img, point, samplesize, (0, 255, 0), -1)
        cv2.circle(mask, point, samplesize, 255, -1)
        img2 = np.copy(img)
        cv2.circle(img2, point, samplesize, (255, 0, 0), 1)
        cv2.imshow('image', img2)

    if (event == cv2.EVENT_MOUSEMOVE):
        point = (x, y)
        if drawing:
            cv2.circle(img, point, samplesize, (0, 255, 0), -1)
            cv2.circle(mask, point, samplesize, 255, -1)
        img2 = np.copy(img)
        cv2.circle(img2, point, samplesize, (255, 0, 0), 1)
        cv2.imshow('image', img2)


    if (event == cv2.EVENT_LBUTTONUP and drawing):
        drawing = False

frame=cv2.imread("balls.png")
cv2.imshow("image",frame)

drawing=False
img = np.copy(frame)
cv2.setMouseCallback('image',draw_mask)

cv2.waitKey(0)

CHANNELS,RANGES,BUCKETS=getHistParams()
hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
print mask.shape,hsv.shape
roihist = cv2.calcHist([hsv], CHANNELS, mask, BUCKETS, RANGES)  #3rd parameter is a mask!!

f=open('hist.pyo', 'w')
pickle.dump(roihist, f)

cv2.destroyAllWindows()
