#include "pk_kinect.h"
#include <iostream>



Kinect::Kinect()
{
	this->sensor = NULL;
	this->frame = NULL;
	this->reader = NULL;
	this->mapper = NULL;
}

Kinect::~Kinect()
{

}

bool Kinect::initialize()
{
	if (SUCCEEDED(GetDefaultKinectSensor(&this->sensor)))
	{
		this->sensor->get_CoordinateMapper(&this->mapper);
		this->sensor->Open();
		this->sensor->OpenMultiSourceFrameReader(FrameSourceTypes::FrameSourceTypes_Depth | FrameSourceTypes::FrameSourceTypes_Color | FrameSourceTypes_Infrared, &this->reader);
		return true;
	}
	return false;
}

bool Kinect::fetch()
{
	if (SUCCEEDED(this->reader->AcquireLatestFrame(&this->frame)))
	{
		return true;
	}
	return false;
}

// get RGBA image, 8 bit
void Kinect::getRgba(BYTE* buffer)
{
	IColorFrame* color = NULL;
	IColorFrameReference* colorRef = NULL;
	this->frame->get_ColorFrameReference(&colorRef);
	if (SUCCEEDED(colorRef->AcquireFrame(&color)))
	{
		color->CopyConvertedFrameDataToArray(COLOR_WIDTH * COLOR_HEIGHT * 4, buffer, ColorImageFormat_Bgra);
		colorRef->Release();
		color->Release();
	}
}

// get depth image, 16 bit
void Kinect::getDepth(USHORT* buffer)
{
	IDepthFrame* depth = NULL;
	IDepthFrameReference* depthRef = NULL;
	this->frame->get_DepthFrameReference(&depthRef);
	if (SUCCEEDED(depthRef->AcquireFrame(&depth)))
	{
		depth->CopyFrameDataToArray(DEPTH_WIDTH * DEPTH_HEIGHT, buffer);
		depthRef->Release();
		depth->Release();
		depthRef = nullptr;
		depth = nullptr;
	}
}

//get IR image
void Kinect::getIR(USHORT* buffer)
{
	IInfraredFrame* IR = NULL;
	IInfraredFrameReference* IRRef = NULL;
	this->frame->get_InfraredFrameReference(&IRRef);
	if (SUCCEEDED(IRRef->AcquireFrame(&IR)))
	{
		IR->CopyFrameDataToArray(IR_WIDTH * IR_HEIGHT, buffer);
		IRRef->Release();
		IR->Release();
		IRRef = nullptr;
		IR = nullptr;
	}
}
void Kinect::depth2xyz() {

	IDepthFrame* depthframe;
	unsigned int sz;
	unsigned short* buf;

	depthframe->AccessUnderlyingBuffer(&sz, &buf);

	mapper->MapDepthFrameToCameraSpace(DEPTH_WIDTH*DEPTH_HEIGHT, buf, DEPTH_WIDTH*DEPTH_HEIGHT, depth2xyz_arr);

	for (int i = 0; i < DEPTH_WIDTH*DEPTH_HEIGHT; i++) {
		std::cout << buf[i] << "  ";
		//std::cout << (int)depth2xyz[i] << std::endl;
	}


}
