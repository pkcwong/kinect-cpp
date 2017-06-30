#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

GLubyte data[WIDTH * HEIGHT * 4];

int main(int argc, char* argv[])
{
	Kinect* kinect = new Kinect();
	kinect->initialize();
	cv::namedWindow("Kinect");
	while (1)
	{
		bool status = kinect->fetchRGBA(data);
		if (status)
		{
			cv::Mat img = cv::Mat(HEIGHT, WIDTH, CV_8UC4, data).clone();
			cv::imshow("Kinect", img);
		}
		cv::waitKey(30);
	}
}
