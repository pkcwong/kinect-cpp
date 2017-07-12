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
	Kinect kinect;
	kinect.initialize();
	while (1)
	{
		if (kinect.fetch())
		{
			cv::Mat frame(COLOR_HEIGHT, COLOR_WIDTH, CV_8UC4, kinect.getRgba());
			cv::imshow("Kinect", frame);
		}
		cv::waitKey(30);
	}
}
