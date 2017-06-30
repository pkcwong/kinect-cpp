#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

GLubyte data[COLOR_WIDTH * COLOR_HEIGHT * 4];

int main(int argc, char* argv[])
{
	Kinect* kinect = new Kinect();
	kinect->initialize();
	cv::namedWindow("Kinect");
	while (1)
	{
		bool status = kinect->fetch();
		if (status)
		{
			kinect->getRgba(data);
			cv::Mat img = cv::Mat(COLOR_HEIGHT, COLOR_WIDTH, CV_8UC4, data).clone();
			cv::imshow("Kinect", img);
		}
		cv::waitKey(30);
	}
}
