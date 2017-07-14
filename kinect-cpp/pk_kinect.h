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

namespace kinect
{

	bool initialize();
	void close();
	bool fetch();
	BYTE* getRgba();
	USHORT* getDepth();
	USHORT* getIr();

};

#endif
