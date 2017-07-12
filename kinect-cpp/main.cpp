#include "pk_kinect.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <gl/GL.h>
#include <iostream>

USHORT IR[IR_WIDTH * IR_HEIGHT];
USHORT depth[DEPTH_WIDTH * DEPTH_HEIGHT];
BYTE color[COLOR_WIDTH * COLOR_HEIGHT *4];

int main(int argc, char* argv[])
{
	Kinect kinect;
	kinect.initialize();
	cv::namedWindow("Kinect");
	while (1) {
		if (kinect.fetch()) {
			kinect.getDepth(depth);

			//for (int i = 0; i < DEPTH_HEIGHT * DEPTH_WIDTH; i++) {
				//depth[i] = depth[i] * 20;
				//std::cout << (int)color[i] << std::endl;
				//	std::cout << depth[i] << std::endl;
			//}
			//}
			kinect.depth2xyz();

			cv::Mat img(DEPTH_HEIGHT, DEPTH_WIDTH, CV_16U, depth);
			cv::imshow("Kinect", img);
			cv::waitKey(30);
		}
			//	for (int i = 0; i < DEPTH_HEIGHT * DEPTH_WIDTH ; i++) {

					//std::cout << (int)color[i] << std::endl;
				//	std::cout << depth[i] << std::endl;
				//}
			
		}
	//cv::cvtColor(img, img, CV_BGR2GRAY);

	//cv::SiftFeatureDetector detector;
	//std::vector<cv::KeyPoint> keypoints;
	//detector.detect(img, keypoints);

	//cv::drawKeypoints(img, keypoints, img);

	//cv::waitKey(20);
}
