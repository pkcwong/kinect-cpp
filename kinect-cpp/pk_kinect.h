#ifndef _PK_KINECT
#define _PK_KINECT

#include <Windows.h>
#include <Ole2.h>

#include <Kinect.h>

namespace kinect
{

	const int COLOR_WIDTH = 1920;
	const int COLOR_HEIGHT = 1080;
	const int DEPTH_WIDTH = 512;
	const int DEPTH_HEIGHT = 424;
	const int IR_WIDTH = 512;
	const int IR_HEIGHT = 424;

	bool initialize();
	void close();
	bool fetch();
	BYTE* getRgba();
	USHORT* getDepth();
	USHORT* getIr();

};

#endif
