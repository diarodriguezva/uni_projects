#ifndef TRACKABLE_H
#define TRACKABLE_H

#include <cv.h>
#include <iostream>

using namespace cv;
using namespace std;

class Trackable {
public:
    Trackable();
    Trackable(Scalar, Scalar, float, std::string);
    ~Trackable();

    Mat getMask (Mat, bool preprocess=true);
    Mat preProcesing(Mat);
    Vec3f updatePosition(Mat);
    void drawOnto(Mat);
    Vec3f get3Dcoordinates();
    Vec2f get2Dcoordinates();
    void drawBalls(Mat);
    void findBalls(Mat, Mat);
    int* findBoxes(Mat, Mat);
private:
    Scalar minHSV,maxHSV;
    std::string name;
    float x, y, radius, realDiameter;
    Point lastImageSize;
    bool found, found_boxes;

    vector<vector<Point> > contours;
    deque<float> x_deque;
    deque<float> y_deque;
    deque<float> radius_deque;

    int elem_deque;

    void median();
    void printDeque();

    Rect* getROI();
    bool getContours(Mat);
};


#endif // TRACKABLE_H
