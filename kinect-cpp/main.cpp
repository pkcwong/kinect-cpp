#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <gl/GL.h>

USHORT data[IR_WIDTH * IR_HEIGHT];

int main(int argc, char* argv[])
{
	Kinect kinect;
	kinect.initialize();
	cv::namedWindow("Kinect");
	while (!kinect.fetch());
	while (1) {

		kinect.getIR(data);
		cv::Mat img(IR_HEIGHT, IR_WIDTH, CV_8UC2, data);
		cv::imshow("Kinect", img);
	}
	//cv::cvtColor(img, img, CV_BGR2GRAY);

	//cv::SiftFeatureDetector detector;
	//std::vector<cv::KeyPoint> keypoints;
	//detector.detect(img, keypoints);

	//cv::drawKeypoints(img, keypoints, img);

	cv::waitKey(20);
}
