#ifndef _PK_KINECT
#define _PK_KINECT

#define COLOR_WIDTH 1920
#define COLOR_HEIGHT 1080
#define DEPTH_WIDTH 512
#define DEPTH_HEIGHT 424

#include <Windows.h>
#include <Ole2.h>

#include <Kinect.h>

#include <gl/GL.h>

class Kinect
{

	private:
	IKinectSensor* sensor;
	IMultiSourceFrame* frame;
	IMultiSourceFrameReader* reader;
	ICoordinateMapper* mapper;

	public:
	Kinect();
	~Kinect();
	bool initialize();
	bool fetch();
	void getRgba(GLubyte* buffer);
	void getDepth(GLubyte* buffer);

};

#endif
