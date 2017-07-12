#include "pk_kinect.h"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <gl/GL.h>

GLubyte data[COLOR_WIDTH * COLOR_HEIGHT * 4];

int main(int argc, char* argv[])
{
	Kinect kinect;
	cv::namedWindow("Kinect");
	kinect.initialize();
	while (1)
	{
		if (kinect.fetch())
		{
			cv::SiftFeatureDetector detector(500);
			std::vector<cv::KeyPoint> keypoints;
			keypoints.reserve(100000);
			kinect.getRgba(data);
			cv::Mat color(COLOR_HEIGHT, COLOR_WIDTH, CV_8UC4, data);
			cv::Mat gray;
			cv::cvtColor(color, gray, CV_BGRA2GRAY);
			detector.detect(gray, keypoints);
			cv::drawKeypoints(gray, keypoints, gray);
			cv::imshow("Kinect", gray);
		}
		cv::waitKey(30);
	}
}
