#include "pk_kinect.h"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\video\video.hpp>
#include <gl/GL.h>

GLubyte data[COLOR_WIDTH * COLOR_HEIGHT * 4];

int main(int argc, char* argv[])
{
	cv::BackgroundSubtractorMOG2 mog;
	kinect::initialize();
	while (1)
	{
		if (kinect::fetch())
		{
			cv::Mat color(COLOR_HEIGHT, COLOR_WIDTH, CV_8UC4, kinect::getRgba());
			cv::Mat gray;
			cv::Mat mask;
			cv::cvtColor(color, gray, CV_BGRA2GRAY);
			mog(gray, mask, 0.01);
			cv::imshow("mask", color);
		}
		cv::waitKey(30);
	}
}
