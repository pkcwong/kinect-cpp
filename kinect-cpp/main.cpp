#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <gl/GL.h>

USHORT IR[IR_WIDTH * IR_HEIGHT];
USHORT depth[DEPTH_WIDTH * DEPTH_HEIGHT];
USHORT color[COLOR_WIDTH * COLOR_HEIGHT];

int main(int argc, char* argv[])
{
	Kinect kinect;
	kinect.initialize();
	cv::namedWindow("Kinect");
	while (!kinect.fetch());
	while (1) {

		kinect.getDepth(depth);
		for (int i = 0; i < DEPTH_WIDTH * DEPTH_HEIGHT; i++) {
			depth[i] = (depth[i] * 256) % 32768;
			}
		cv::Mat img(DEPTH_HEIGHT,DEPTH_WIDTH, CV_16U, depth);
		cv::imshow("Kinect", img);
		cv::waitKey(30);
	}
	//cv::cvtColor(img, img, CV_BGR2GRAY);

	//cv::SiftFeatureDetector detector;
	//std::vector<cv::KeyPoint> keypoints;
	//detector.detect(img, keypoints);

	//cv::drawKeypoints(img, keypoints, img);

	//cv::waitKey(20);
}
