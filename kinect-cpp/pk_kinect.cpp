#include "pk_kinect.h"

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
	}
}

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
	}
}
