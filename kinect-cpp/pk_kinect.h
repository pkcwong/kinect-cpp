#ifndef _PK_KINECT
#define _PK_KINECT

#define COLOR_WIDTH 1920
#define COLOR_HEIGHT 1080
#define DEPTH_WIDTH 512
#define DEPTH_HEIGHT 424
#define IR_WIDTH 512
#define IR_HEIGHT 424

#include <Windows.h>
#include <Ole2.h>

#include <Kinect.h>

class Kinect
{

	private:
	IKinectSensor* sensor;
	IMultiSourceFrame* frame;
	IMultiSourceFrameReader* reader;
	ICoordinateMapper* mapper;
	float X, Y, Z;
	//IDepthFrame* depthframe;
	CameraSpacePoint depth2xyz_arr[DEPTH_WIDTH*DEPTH_HEIGHT];


	public:
	Kinect();
	~Kinect();
	bool initialize();
	bool fetch();
	void getRgba(BYTE* buffer);
	void getDepth(USHORT* buffer);
	void getIR(USHORT* buffer);
	void depth2xyz(float depth, int lineNumber, int pixelNumber);

};

#endif
