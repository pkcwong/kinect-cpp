#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <gl/GL.h>

GLubyte data[COLOR_WIDTH * COLOR_HEIGHT * 4];

int main(int argc, char* argv[])
{
	Kinect kinect;
	kinect.initialize();
	cv::namedWindow("Kinect");
	while (!kinect.fetch());
	kinect.getRgba(data);
	cv::Mat img(COLOR_HEIGHT, COLOR_WIDTH, CV_8UC4, data);

	cv::cvtColor(img, img, CV_BGR2GRAY);

	cv::SiftFeatureDetector detector;
	std::vector<cv::KeyPoint> keypoints;
	detector.detect(img, keypoints);

	cv::drawKeypoints(img, keypoints, img);

	cv::imshow("Kinect", img);
	cv::waitKey(0);
}
