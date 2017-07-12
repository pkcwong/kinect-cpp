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
	BYTE* colorData;
	USHORT* depthData;
	USHORT* irData;

	public:
	Kinect();
	~Kinect();
	bool initialize();
	bool fetch();
	BYTE* getRgba();
	USHORT* getDepth();
	USHORT* getIr();

};

#endif
