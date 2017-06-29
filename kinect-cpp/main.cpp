#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char* argv[])
{
	cv::Mat image = cv::imread("./res/opencv-logo.png", cv::IMREAD_COLOR);
	cv::namedWindow("Kinect", cv::WINDOW_AUTOSIZE);
	cv::imshow("Kinect", image);
	cv::waitKey(0);
}
