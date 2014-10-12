import numpy as np
import cv2
import cv2.cv
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import scipy.spatial
from scipy      import optimize
import time
import math
import pickle
from os import wait

__author__ = 'moses'

def sample_color(event,x,y,flags,param):
    global points,drawing

    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        points=[]

    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing == True:
            points.append((x,y))

    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        find_balls(img)

def drawRectangle(event,x,y,flags,param):
    global frame,select_flag,drawing,point1,point2,img1
    if (event == cv2.EVENT_LBUTTONDOWN):
        #/* left button clicked. ROI selection begins */
        point1 = (x, y)
        drawing = True

    if (event == cv2.EVENT_MOUSEMOVE and drawing):
        #/* mouse dragged. ROI being selected */
        img1 = np.copy(img)
        point2 = (x, y)
        cv2.rectangle(img1, point1, point2, (255, 0, 0), 3, 8, 0)
        cv2.imshow('image', img1)

    if (event == cv2.EVENT_LBUTTONUP and drawing):
        point2 = (x, y)
        drawing = False
        cv2.imshow('image', img1)
        find_balls(img)


def get_color_range(hsv,pixels):
    lower_bound = np.array([255, 255, 255])
    upper_bound = np.array([0, 0, 0])
    for pixel in pixels:
        for i in [0, 1, 2]:
            lower_bound[i] = min(lower_bound[i], pixel[i])
            upper_bound[i] = max(upper_bound[i], pixel[i])
    print(lower_bound)
    print(upper_bound)
    return lower_bound, upper_bound


def getPixelsAt(hsv, points):
    pixels = []
    for point in points:
        pixels.append(hsv[point[0], point[1]])
    pixels = np.array(pixels)
    return pixels


def plot3D(pixels):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    a, b, c = np.hsplit(pixels, 3)
    ax.scatter(a, b, c)
    plt.show()


def analyze_colors(hsv,pixels):
    plot3D(pixels)
    pMean = np.mean(pixels, axis=0)
    pCov = np.cov(pixels.T) #transpose
    return pMean, pCov


def buildMahalanobisMask( hsv, invcov, mean, w, h):
    mask = np.zeros((w, h), np.uint8)
    mindist = float("inf")
    maxdist = 0
    for x in range(w):
        for y in range(h):
            dist = scipy.spatial.distance.mahalanobis(mean, hsv[x][y], invcov);
            mask[x, y] = dist
            mindist = min(mindist, dist)
            maxdist = max(maxdist, dist)
    print(mindist)
    print(maxdist)
    ret, thresh = cv2.threshold(mask, 10, 255, cv2.THRESH_TRUNC)
    thresh *= 255 / 10
    thresh = 255 - thresh
    return thresh

def showChannels(hsv):
    h, s, v = cv2.split(hsv)
    cv2.imshow("h", h)
    cv2.imshow("s", s)
    cv2.imshow("v", v)

def matchHistogram(CHANNELS, RANGES, hsv, roihist):
    # normalize histogram and apply backprojection
    cv2.normalize(roihist, roihist, 0, 255, cv2.NORM_MINMAX)
    dst = cv2.calcBackProject([hsv], CHANNELS, roihist, RANGES, 1)
    return dst


def histogramBackproj(hsv, obj_hsv, obj_mask=None):
    CHANNELS = [0, 1]
    RANGES = [0, 256, 0, 256]
    BUCKETS = [30, 10]
    # calculating object histogram
    roihist = cv2.calcHist([obj_hsv], CHANNELS, obj_mask, BUCKETS, RANGES)  #3rd parameter is a mask!!

    mask = matchHistogram(CHANNELS, RANGES, hsv, roihist)
    return mask


def circleFrom3Points(sample):
    x = sample[:,0, 0]
    y = sample[:,0, 1]
    ma = (y[1] - y[0]) / (x[1] - x[0])
    mb = (y[2] - y[1]) / (x[2] - x[1])
    xc = (ma * mb * (y[0] - y[2]) + mb * (x[0] + x[1]) - ma * (x[1] + x[2])) / (2 * (mb - ma))
    yc = (-1 / ma) * (xc - (x[0] + x[1]) / 2) + (y[0] + y[1]) / 2
    r = math.sqrt((xc - x[0]) ** 2 + (yc - y[0]) ** 2)
    xc = int(xc)
    yc = int(yc)
    #c=int(c[0]),int(c[1])
    c = (xc, yc)
    r = int(r)
    return c, r

def cv2findNonZero(img):
    ppnp = np.transpose(np.nonzero(img))
    ppnp[:,[0,1]]=ppnp[:,[1,0]]
    return ppnp

def calc_R(xc, yc,x,y):
    """ calculate the distance of each 2D points from the center (xc, yc) """
    return np.sqrt((x-xc)**2 + (y-yc)**2)

def f_2(c,x,y):
    """ calculate the algebraic distance between the data points and the mean circle centered at c=(xc, yc) """
    Ri = calc_R(c[0],c[1],x,y)
    return Ri - Ri.mean()


def longestContour(contours):
    cnt = contours[0]
    maxlength = 0;
    for contour in contours:
        if cv2.arcLength(contour, True) > maxlength:
            maxlength = cv2.arcLength(contour, True)
            cnt = contour
    return cnt


def optimizeCircle(center_estimate, x, y):
    center_2, ier = optimize.leastsq(lambda a: f_2(a, x, y), center_estimate)
    xc_2, yc_2 = center_2
    Ri_2 = calc_R(center_2[0], center_2[1], x, y)
    R_2 = Ri_2.mean()
    residu_2 = sum((Ri_2 - R_2) ** 2)
    return center_2, R_2, residu_2/len(x)


def fitCircle_leastSquares(cnt):
    M = cv2.moments(cnt)
    cx = int(M['m10']/M['m00'])
    cy = int(M['m01']/M['m00'])

    x=cnt[:,0][:,0]
    y=cnt[:,0][:,1]

    # coordinates of the barycenter
    x_m = np.mean(x)
    y_m = np.mean(y)

    # calculation of the reduced coordinates
    u = x - x_m
    v = y - y_m

    # linear system defining the center (uc, vc) in reduced coordinates:
    #    Suu * uc +  Suv * vc = (Suuu + Suvv)/2
    #    Suv * uc +  Svv * vc = (Suuv + Svvv)/2
    Suv  = sum(u*v)
    Suu  = sum(u**2)
    Svv  = sum(v**2)
    Suuv = sum(u**2 * v)
    Suvv = sum(u * v**2)
    Suuu = sum(u**3)
    Svvv = sum(v**3)

    # Solving the linear system
    A = np.array([ [ Suu, Suv ], [Suv, Svv]])
    B = np.array([ Suuu + Suvv, Svvv + Suuv ])/2.0
    uc, vc = np.linalg.solve(A, B)

    xc_1 = x_m + uc
    yc_1 = y_m + vc

    # Calcul des distances au centre (xc_1, yc_1)
    Ri_1     = np.sqrt((x-xc_1)**2 + (y-yc_1)**2)
    R_1      = np.mean(Ri_1)
    residu_1 = sum((Ri_1-R_1)**2)

    center_estimate = xc_1,yc_1
    center_2, R_2, residu_2 = optimizeCircle(center_estimate, x, y)
    R_2        = Ri_2.mean()
    residu_2   = sum((Ri_2 - R_2)**2)
    center_2=tuple(map(int,center_2))
    #print center_2
    return center_2, int(R_2), residu_2
    #map(max,contours)

def fitCircle_blobs(mask):
    contours, hierarchy = cv2.findContours(mask,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
    cnt = contours[0]
    maxlength=0;
    for contour in contours:
        if cv2.arcLength(contour,True)>maxlength:
            maxlength=cv2.arcLength(contour,True)
            cnt=contour
    M = cv2.moments(cnt)
    cx = int(M['m10']/M['m00'])
    cy = int(M['m01']/M['m00'])
    print M
    ellipse = cv2.fitEllipse(cnt)
    print ellipse
    r=(ellipse[1][0]+ellipse[1][1])/2
    return (cx,cy),int(ellipse[2])
    #map(max,contours)


def fitCircle(cnt):
    c = (0,0)
    r = 0

    #print ballContourPoints.shape  # (n, 2)
    MARGIN = 3
    MIN_RADIUS = 30
    MAX_RADIUS = 400
    r = 0
    PROBABILITY = 0.95
    N = float('Inf')
    max_Iterations=120
    totalNumberOfPoints = len(cnt)
    sampleCount = 0
    bestInlierCount = 0
    bestSample = None
    bestInliers = None
    #abfangen falls kein ball da ist (totalNumberOfPoints=0)
    if totalNumberOfPoints == 0:
        return c, r
    while sampleCount < N and sampleCount < max_Iterations:
        while not MIN_RADIUS < r < MAX_RADIUS:
            #sampleIDs = np.random.choice(range(totalNumberOfPoints),3)
            sampleIDs=np.random.randint(0, totalNumberOfPoints, 3) #TODO not the same twice
            sample = cnt[sampleIDs]

            #TODO check determinante
            # mat=sample[0].append(1).T
            # mat=sample.T.append([1, 1, 1])
            # print mat
            # det=np.linalg.det(mat)

            c, r = circleFrom3Points(sample)

        # cv2.imshow("model", inlierMask)
        # cv2.imshow("inlier", inlierImg)
        # cv2.waitKey(0)

        centerpoint=np.array(c)
        inliers=[]
        for point in cnt:
            if abs(np.linalg.norm(np.array(point[0])-centerpoint)-r)<MARGIN:
                inliers.append(point)
        inlierCount = len(inliers)

        #print inlierCount

        if inlierCount > bestInlierCount:
            bestInlierCount = inlierCount
            bestSample = sample
            bestInliers=inliers

        #TODO how can inliercount be 0 ?!
        if inlierCount == 0:
            continue
        epsilon = 1.0 - float(inlierCount) / float(totalNumberOfPoints)
        N = math.log(1.0 - PROBABILITY) / math.log(1.0 - (1.0 - epsilon) ** 3);
        #print N
        sampleCount += 1
        r = 0
    print "iterations in ransac", sampleCount

    c,r = circleFrom3Points(bestSample)
    return  c,r,bestInlierCount/len(cnt)

def find_balls(frame):
    ##preprocessing
    kernel = cv2.getGaussianKernel(10, 4)
    kernel=kernel*kernel.T
    cv2.filter2D(frame,-1, frame, kernel)

    ##color conversion
    hsv=cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    #showChannels(hsv)


    if RECTANGLE:
        #rect = (point1[0], point1[1], point2[0] - point1[0], point2[1] - point1[1]);
        obj_img = hsv[point1[1]:point2[1],point1[0]:point2[0],0:3];
        #pixels=array(obj_img)
    else:
        pixels = getPixelsAt(hsv, points)
        obj_img=[pixels]
        obj_img=np.array(obj_img)


    ##### Thesholding ####
    #lower_bound, upper_bound = get_color_range(hsv,pixels)
    #mask = cv2.inRange(hsv, lower_bound, upper_bound)

    ####Mahalanobis#####
    #mean,cov=analyze_colors(hsv,pixels)
    #invcov=np.linalg.inv(cov)
    #(w,h,c) = hsv.shape
    #mask = buildMahalanobisMask(hsv, invcov, mean, w, h)

    #### Histogram Backprojection ####
    mask = histogramBackproj(hsv, obj_img)
    center2, radius2 = findBallInMask(frame, hsv, mask)

    return center2, radius2

def test():
    drawing=False
    points=[]

    img=cv2.imread("balls.jpg")
    cv2.imshow("image",img)

    print img.shape

    RECTANGLE=True
    if RECTANGLE:
        cv2.setMouseCallback('image',drawRectangle)
    else:
        cv2.setMouseCallback('image',sample_color)

    cv2.waitKey(0)
    cv2.destroyAllWindows()