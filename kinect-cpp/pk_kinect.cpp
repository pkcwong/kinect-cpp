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
		this->sensor->OpenMultiSourceFrameReader(FrameSourceTypes::FrameSourceTypes_Depth | FrameSourceTypes::FrameSourceTypes_Color, &this->reader);
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

void Kinect::getRgba(GLubyte* buffer)
{
	IColorFrame* color = NULL;
	IColorFrameReference* colorRef = NULL;
	this->frame->get_ColorFrameReference(&colorRef);
	colorRef->AcquireFrame(&color);
	color->CopyConvertedFrameDataToArray(COLOR_WIDTH * COLOR_HEIGHT * 4, buffer, ColorImageFormat_Bgra);
	colorRef->Release();
	color->Release();
}

void Kinect::getDepth(GLubyte* buffer)
{
	IDepthFrame* depth = NULL;
	IDepthFrameReference* depthRef = NULL;
	this->frame->get_DepthFrameReference(&depthRef);
	depthRef->AcquireFrame(&depth);
}
