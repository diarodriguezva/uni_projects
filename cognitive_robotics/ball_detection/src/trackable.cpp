#include "trackable.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <iostream>
#include <cxcore.h>
#include <X11/keysym.h>

//#define FOCAL_DISTANCE 1308
//#define X_AXIS_CAMERA 655
//#define Y_AXIS_CAMERA 329

#define FOCAL_DISTANCE 1310
#define X_AXIS_CAMERA 645
#define Y_AXIS_CAMERA 306

#define PI 3.141592

using namespace cv;
using namespace std;

Trackable::Trackable(Scalar minHSV, Scalar maxHSV, float realDiameter, std::string name){
    x = 0;
    y = 0;
    radius = 0;
    found=false;
    elem_deque = 0;
    this->minHSV = minHSV;
    this->maxHSV = maxHSV;
    this->realDiameter = realDiameter;
    this->name = name;
}

Trackable::Trackable(){
    x = 0;
    y = 0;
    radius = 0;
    found=false;
}

Trackable::~Trackable(){}

Mat Trackable::getMask (Mat hsvImage, bool preprocess) {
    Mat mask;
    if (minHSV[0] > maxHSV[0]){ //if hue range goes over 255 (eg red from min 200 to max 50)
        Mat mask1, mask2;
        Scalar min1, max1, min2, max2;
        min1 = minHSV;
        min2 = minHSV;
        max1 = maxHSV;
        max2 = maxHSV;
        max1[0] = 255;
        min2[0] = 0;
        inRange(hsvImage,min1,max1,mask1);
        inRange(hsvImage,min2,max2,mask2);
        mask=mask1+mask2;
        //imshow("mask", mask);

    } else {
        inRange(hsvImage,minHSV,maxHSV,mask);
    }
    if (preprocess)
        mask=preProcesing(mask);
    return mask;
}

Mat Trackable::preProcesing(Mat in){
    Mat mor_img, img_aux;
    Mat Kernel(Size(3, 3), CV_8UC1);
    Kernel.setTo(Scalar(1));

    // First Erode-Dilate in order to supress noisy
    erode(in,mor_img,Kernel,Point(-1,-1),1);
    dilate(mor_img,mor_img,Kernel,Point(-1,-1),1);

    // Second, Dilate-Erode to close Areas
    dilate(mor_img,mor_img,Kernel,Point(-1,-1),4);
    erode(mor_img,mor_img,Kernel,Point(-1,-1),4);

    GaussianBlur(mor_img,img_aux,Size(11,11),0,0);

    return img_aux;
}

bool Trackable::getContours(Mat image){

    lastImageSize = image.size();

    Mat mask = getMask(image);
    imshow("mask", mask);

    Mat img_canny;
    Canny(mask,img_canny,50,100);
    imshow("Canny", img_canny);

    vector<Vec4i> hierarchy;

    findContours( img_canny, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    if(contours.size()>0)
        return true;
    else
        return false;
}

void Trackable::findBalls(Mat image, Mat original_img){ //find circle initially

    found = false;

    if(!getContours(image)){
        return;
    }

    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    }

    Mat drawing_balls = Mat::zeros( original_img.size(), CV_8UC3 );

    for( int i = 0; i< contours.size(); i++ )
    {
        drawContours( drawing_balls, contours_poly, i, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
        Size rect_size = boundRect[i].size();

        double area = contourArea(contours_poly[i]);
        double perimeter = arcLength(contours_poly[i],1);
        double roundness = 0;
        if (perimeter > 0)
            roundness = 4*PI*area/(perimeter*perimeter);

        //cout << "Roundness: " << roundness << endl;

        float rel = 0;
        if (rect_size.height > rect_size.width){
            rel = (float)rect_size.width/rect_size.height;
        }
        else{
            rel = (float)rect_size.height/rect_size.width;
        }

        if( rel > 0.7 && rect_size.width > 200 && rect_size.height > 200 && roundness > 0){
//            cout << "Roundness: " << roundness << endl;
//            cout << "Rel: " << rel << endl;
//            cout << "Width: " << rect_size.width << endl;
//            cout << "Height: " << rect_size.height << endl;

            radius = rect_size.width/2;
            x = boundRect[i].x + radius;
            y = boundRect[i].y + radius;
            found = true;

            rectangle( drawing_balls, boundRect[i].tl(), boundRect[i].tl() + Point(2*radius,2*radius), Scalar(0,255,255), 2, 8, 0 );
            circle(drawing_balls, Point(x,y), radius, Scalar(255,255,0),1,8,0);
            //circle(original_img, Point(x,y), radius, Scalar(255,255,0),1,8,0);
            //circle(original_img, Point(x,y), 2, Scalar(0,255,0), -1, 8, 0 );  // circle center
        }
    }

    if(found){
        //cout << "x: " << x << " y: " << y << " radius: " << radius << endl;
        x_deque.push_back(x);
        y_deque.push_back(y);
        radius_deque.push_back(radius);
    }
    else{
        x_deque.push_back(0);
        y_deque.push_back(0);
        radius_deque.push_back(0);
    }

    if(x_deque.size() > 5){
        x_deque.pop_front();
        y_deque.pop_front();
        radius_deque.pop_front();
    }

    //printDeque();
    imshow( "Contours_balls", drawing_balls );
}

void Trackable::printDeque(){
    cout << "Elem_deque: " << x_deque.size() << endl;
    for(int i=0; i < (x_deque.size()) ; i++){
        cout << "x[" << i << "]: " << x_deque[i] << " ";
        cout << "radius[" << i << "]: " << radius_deque[i] << " ";
    }
    cout << endl;
}

int* Trackable::findBoxes(Mat image, Mat original_img){ //find circle initially

    found_boxes = false;

    if(!getContours(image))
        return NULL;

    int corners[4];
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    //vector<RotatedRect> enclosingRect( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        //enclosingRect[i] = minAreaRect( Mat(contours_poly[i]) );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
    }

    Mat drawing_boxes = Mat::zeros( original_img.size(), CV_8UC3 );

    for( int i = 0; i< contours.size(); i++ )
    {
        drawContours( drawing_boxes, contours_poly, i, Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
        Size rect_size = boundRect[i].size();

        double area = contourArea(contours_poly[i]);
        double perimeter = arcLength(contours_poly[i],1);
        double roundness = 4*PI*area/(perimeter*perimeter);

        if( rect_size.width > 200 && rect_size.height > 200 && roundness < 0.78){
            corners[0] = boundRect[i].tl().x;  // x_min
            corners[1] = boundRect[i].br().x; // x_max
            corners[2] = boundRect[i].tl().y; // y_max
            corners[3] = boundRect[i].br().y; // y_min

            found_boxes = true;

            rectangle(drawing_boxes, boundRect[i], Scalar(0,255,255),2,8,0);
            rectangle(original_img, boundRect[i], Scalar(0,255,255),2,8,0);
        }
    }

    //imshow( "Contours boxes", drawing_boxes );
    return corners;
}

Vec3f Trackable::updatePosition(Mat image){

    Vec3f *circle;

    /* sets the Region of Interest
       Note that the rectangle area has to be __INSIDE__ the image */
    Rect* roi = getROI();
    Mat roi_image = image(*roi);

    vector<Vec3f> circles;
    Mat mask = getMask(roi_image);
    HoughCircles( mask, circles, CV_HOUGH_GRADIENT, 1, mask.rows/4, 100, 20, 20, 0 );

    if(circles.size() > 0){
        *circle=circles[0];
        //consider shift of subimge
        (*circle)[0] += roi->x;
        (*circle)[1] += roi->y;
        found = true;
    } else {
        //in case there wasn't a circle in the Region Of Interest, search the whole image.
        //circle=find(image);
        if (circle==NULL) {
            return NULL;
        }
    }

    x = (*circle)[0];
    y = (*circle)[1];
    radius = (*circle)[2];
    return *circle;
}

Rect* Trackable::getROI(){
    int maxshift=30; // in pixels
    int offset = radius+maxshift/2;
    int windowsize = 2*radius+maxshift;
    return new Rect(x-offset, y-offset, windowsize, windowsize);
}

void Trackable::drawOnto(Mat thisIimage){
    //TODO  check if imagesize fits
    Point center(x,y);
    circle( thisIimage, center, 3, Scalar(0,255,0), -1, 8, 0 );  // circle center
    circle( thisIimage, center, radius, Scalar(0,0,255), 3, 8, 0 ); // circle outline
}

void Trackable::median(){
    deque<float> x_aux = x_deque;
    deque<float> y_aux = y_deque;
    deque<float> radius_aux = radius_deque;
    sort(x_aux.begin(), x_aux.end());
    sort(y_aux.begin(), y_aux.end());
    sort(radius_aux.begin(), radius_aux.end());

    x = x_aux[2];
    y = y_aux[2];
    radius = radius_aux[2];
}

Vec3f Trackable::get3Dcoordinates(){

    median();
    //printDeque();
    if (radius > 0){
        float z_tilde = realDiameter*FOCAL_DISTANCE/1280*lastImageSize.x/(2*radius);
        float z = 0.9752*z_tilde + 2.2137; // Gleichung
        float x = -z*(X_AXIS_CAMERA/1280*lastImageSize.x - (this->x-lastImageSize.x/2))/FOCAL_DISTANCE;
        float y = -z*(Y_AXIS_CAMERA/720*lastImageSize.y - (this->y-lastImageSize.y/2))/FOCAL_DISTANCE;
        return Vec3f(x,y,z);
    }
    else
      return Vec3f(0,0,0);
}

Vec2f Trackable::get2Dcoordinates(){

    median();
    if (radius > 0)
        return Vec2f(x,y);
    else
        return Vec2f(0,0);
}

void Trackable::drawBalls(Mat original_img){

    //printDeque();
    if(x_deque.size()>=5){
        x = x_deque[2];
        y = y_deque[2];
        radius = radius_deque[2];

        if(radius > 0){
            circle(original_img, Point(x,y), radius, Scalar(255,255,0),1,8,0);
            circle(original_img, Point(x,y), 2, Scalar(0,255,0), -1, 8, 0 );
        }
        else{
            circle(original_img, Point(0,0), 1, Scalar(255,255,0),1,8,0);
        }
    }
}
