#ifndef _PK_KINECT
#define _PK_KINECT

#define WIDTH 1920
#define HEIGHT 1080

#include <Windows.h>
#include <Ole2.h>

#include <Kinect.h>

#include <gl/GL.h>

class Kinect
{

	private:
	IKinectSensor* sensor;
	IColorFrameReader* reader;

	public:
	Kinect();
	~Kinect();
	bool initialize();
	bool fetchRGBA(GLubyte* buffer);

};

#endif
