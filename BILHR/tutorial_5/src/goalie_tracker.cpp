/*
 * goalie_tracker.cpp
 *      Author: George Mesesan
 */

#include <boost/smart_ptr/shared_ptr.hpp>
#include <BILHR_ros/GoaliePos.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <image_transport/subscriber.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <ros/console.h>
#include <ros/init.h>
#include <ros/node_handle.h>
#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <rosconsole/macros_generated.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/String.h>
#include <stddef.h>
#include <algorithm>
#include <vector>

using namespace std;
using namespace cv;

namespace enc = sensor_msgs::image_encodings;

// label of the GUI window showing the raw image of NAO's camera
static const char cam_window[] = "NAO Camera (raw image)";

ros::Publisher tracker_pub;

int step = 10;
//int min_saturation = 160;
//int max_saturation = 255;
//int min_value = 90;
//int max_value = 255;
//int min_hue = 165;
//int max_hue = 5;

int min_saturation = 145;
int max_saturation = 255;
int min_value = 185;
int max_value = 255;
int min_hue = 10;
int max_hue = 30;

vector<RotatedRect> findGoalPosts(Mat& image) {
	int min_saturation = 160;
	int max_saturation = 255;
	int min_value = 90;
	int max_value = 255;
	int min_hue = 165;
	int max_hue = 5;

	Mat hsv_image, thresh_image;

	// convert to HSV
	cvtColor(image, hsv_image, CV_BGR2HSV);

	// threshold around hue=175, use inRange twice because of circular values of hue (wraps around at 179)
	if (max_hue < min_hue) {
		Mat thresh_image2;
		inRange(hsv_image, Scalar(min_hue, min_saturation, min_value), Scalar(179, max_saturation, max_value),
				thresh_image);
		inRange(hsv_image, Scalar(0, min_saturation, min_value), Scalar(max_hue, max_saturation, max_value),
				thresh_image2);
		bitwise_or(thresh_image, thresh_image2, thresh_image);
	} else {
		inRange(hsv_image, Scalar(min_hue, min_saturation, min_value), Scalar(max_hue, max_saturation, max_value),
				thresh_image);
	}

	// eliminate noise through morphological opening and closing
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	//morphological opening (removes small objects from the foreground)
	erode(thresh_image, thresh_image, kernel);
	dilate(thresh_image, thresh_image, kernel);

	//morphological closing (removes small holes from the foreground)
	dilate(thresh_image, thresh_image, kernel);
	erode(thresh_image, thresh_image, kernel);

	// Find the contours in the image
	vector<vector<Point> > contours; // Vector for storing contours
	vector<Vec4i> hierarchy;

	findContours(thresh_image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

//    ROS_INFO("%d", contours.size());

	vector<vector<Point> > large_contours;
	for (size_t i = 0; i < contours.size(); i++) { // iterate through each contour.
		double area = contourArea(contours[i], false);  //  Find the area of contour
		if (area > 100)
			large_contours.push_back(contours[i]);
	}

    int max_angle = 45;
    int min_angle = 135;
	vector<RotatedRect> posts;
	for (size_t i = 0; i < large_contours.size(); i++) {
		RotatedRect ell = fitEllipse(large_contours[i]);
        //ROS_INFO("%f", ell.angle);
        if (ell.angle < max_angle || ell.angle > min_angle) {
            posts.push_back(ell);
            ellipse(image, ell, Scalar(255, 0, 0), 2);
        }
        //        ROS_INFO("%f %f", ell.center.x, ell.center.y);
	}

	return posts;
}

Point2f findGoalie(Mat& image) {
	int min_saturation = 145;
	int max_saturation = 255;
	int min_value = 185;
	int max_value = 255;
	int min_hue = 10;
	int max_hue = 30;

	Mat hsv_image, thresh_image;

	// convert to HSV
	cvtColor(image, hsv_image, CV_BGR2HSV);

	// threshold around hue=175, use inRange twice because of circular values of hue (wraps around at 179)
    inRange(hsv_image, Scalar(min_hue, min_saturation, min_value), Scalar(max_hue, max_saturation, max_value), thresh_image);

	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	dilate(thresh_image, thresh_image, kernel);

	int count = 0;
	double x = 0;
	double y = 0;

	for (size_t row = 0; row < thresh_image.rows; row++)
		for (size_t col = 0; col < thresh_image.cols; col++) {
			unsigned char val = thresh_image.at<uchar>(row, col);
			if (val != 0) {
				count++;
				x += row;
				y += col;
			}
		}

	if (count != 0) {
		Point2f goalie_point(y / count, x / count);
		circle(image, goalie_point, 3, Scalar(0, 255, 0), -1, 8, 0);
		//ROS_INFO("%f %f", y / count, x / count);
		return goalie_point;
	} else
		return Point2f(-1, -1);
}

double squareDistance(Point2f point1, Point2f point2) {
	double dx = point1.x - point2.x;
	double dy = point1.y - point2.y;
	return dx * dx + dy * dy;
}

// callback function for vision
void visionCallback(const sensor_msgs::ImageConstPtr& msg) {
	// pointer on OpenCV image
	cv_bridge::CvImagePtr cv_ptr;

	try {
		// transform ROS image into OpenCV image
		cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR8);
	} catch (cv_bridge::Exception& e)		// throw an error msg. if conversion fails
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	Mat image = cv_ptr->image;

	vector<RotatedRect> posts = findGoalPosts(image);
	Point2f goalie_point = findGoalie(image);

    if (posts.size() == 2 && goalie_point.x != -1) {
        Point2f left_post_center = (posts[0].center.x < posts[1].center.x) ? posts[0].center : posts[1].center;
        Point2f right_post_center = (posts[0].center.x < posts[1].center.x) ? posts[1].center : posts[0].center;
        double a_square = squareDistance(goalie_point, left_post_center);
        double b_square = squareDistance(goalie_point, right_post_center);
        double goal_distance = squareDistance(left_post_center, right_post_center);

        int goalie_pos_val = round(3 + 2 * (a_square - b_square) / goal_distance);

        BILHR_ros::GoaliePos goalie_pos;
        goalie_pos.found = true;
        goalie_pos.position = goalie_pos_val;
        tracker_pub.publish(goalie_pos);
    } else {
        BILHR_ros::GoaliePos goalie_pos;
        goalie_pos.found = true;
        goalie_pos.position = 3;
        tracker_pub.publish(goalie_pos);
    }

	// show the raw camera image
	imshow(cam_window, image);
	//imshow("Detector", thresh_image);

	waitKey(3);
}

// callback function for key events
void keyCallback(const std_msgs::String::ConstPtr& msg) {
	char ch = msg->data[0];
	switch (ch) {
	case 'w':
		min_hue -= step;
		break;
	case 'e':
		min_hue += step;
		break;
	case 'i':
		max_hue -= step;
		break;
	case 'o':
		max_hue += step;
		break;
	case 's':
		min_saturation -= step;
		break;
	case 'd':
		min_saturation += step;
		break;
	case 'j':
		max_saturation -= step;
		break;
	case 'k':
		max_saturation += step;
		break;
	case 'x':
		min_value -= step;
		break;
	case 'c':
		min_value += step;
		break;
	case 'n':
		max_value -= step;
		break;
	case 'm':
		max_value += step;
		break;
	case 't':
		step++;
		break;
	case 'g':
		step--;
		break;
	}
	min_hue = max(0, min_hue);
	max_hue = min(255, max_hue);
	min_saturation = max(0, min_saturation);
	max_saturation = min(255, max_saturation);
	min_value = max(0, min_value);
	max_value = min(255, max_value);

	ROS_INFO("hue: %d - %d, saturation: %d - %d, value:%d - %d", min_hue, max_hue, min_saturation, max_saturation,
			min_value, max_value);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "ball_tracker");
	ros::NodeHandle node_handle;

	// messaging with the NAO nodes

	// advertise the target joint states
	tracker_pub = node_handle.advertise<BILHR_ros::GoaliePos>("goalie_tracker", 1);

	// using image_transport to publish and subscribe to images
	image_transport::ImageTransport image_transport(node_handle);

	// subscribe to the raw camera image
	image_transport::Subscriber image_sub;
	image_sub = image_transport.subscribe("image_raw", 1, visionCallback);

	// set up the subscriber for the keyboard
	ros::Subscriber key_sub;
	key_sub = node_handle.subscribe("key", 5, keyCallback);

	// create a GUI window for the raw camera image
	namedWindow(cam_window, 0);

	ros::spin();

	return 0;
}
