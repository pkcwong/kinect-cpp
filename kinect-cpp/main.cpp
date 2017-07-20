#include "pk_kinect.h"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\video\video.hpp>
#include <gl/GL.h>

#include <iostream>

GLubyte data[kinect::COLOR_WIDTH * kinect::COLOR_HEIGHT * 4];

int main(int argc, char* argv[])
{
	cv::BackgroundSubtractorMOG2 mog;
	std::vector<std::vector<cv::Point>> contours;
	kinect::initialize();
	while (1)
	{
		if (kinect::fetch())
		{
			int largest_area = 0;
			int largest_contour_index = 0;
			cv::Rect rect;
			cv::Mat mask;
			cv::Mat frame;
			cv::Mat raw(kinect::COLOR_HEIGHT, kinect::COLOR_WIDTH, CV_8UC4, kinect::getRgba());
			cv::flip(raw, raw, 1);
			cv::cvtColor(raw, frame, cv::COLOR_BGRA2BGR);
			cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);
			cv::inRange(frame, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), frame);
			cv::medianBlur(frame, frame, 5);
			mog(frame, mask, 0.05);
			
			cv::findContours(mask, contours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
			std::cout << contours.size() << "\n";
			for (size_t i = 0; i != contours.size(); i++)
			{
				double area = contourArea(contours[i]);

				if (area > largest_area)
				{
					largest_area = area;
					largest_contour_index = i;
					rect = cv::boundingRect(contours[i]);
				}
			}
			cv::drawContours(mask, contours, largest_contour_index, cv::Scalar(255, 255, 255), 10);
			
			cv::imshow("raw", raw);
			cv::imshow("Kinect", mask);
		}
		cv::waitKey(30);
	}
}
