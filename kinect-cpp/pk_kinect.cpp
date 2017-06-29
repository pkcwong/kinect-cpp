#include "pk_kinect.h"

Kinect::Kinect()
{
	this->sensor = NULL;
	this->reader = NULL;
}

Kinect::~Kinect()
{

}

bool Kinect::initialize()
{
	HRESULT hr = GetDefaultKinectSensor(&this->sensor);
	if (FAILED(hr))
	{
		return hr;
	}
	if (this->sensor)
	{
		IColorFrameSource* framesource = NULL;
		hr = this->sensor->Open();
		if (SUCCEEDED(hr))
		{
			hr = this->sensor->get_ColorFrameSource(&framesource);
		}
		if (SUCCEEDED(hr))
		{
			hr = framesource->OpenReader(&this->reader);
		}
		framesource->Release();
	}
	if (!this->sensor || FAILED(hr))
	{
		return false;
	}
	return true;
}

bool Kinect::fetchRGB(GLubyte* buffer)
{
	IColorFrame* frame = NULL;
	if (SUCCEEDED(reader->AcquireLatestFrame(&frame)))
	{
		if (frame)
		{
			frame->CopyConvertedFrameDataToArray(WIDTH * HEIGHT * 4, buffer, ColorImageFormat_Bgra);
			frame->Release();
			return true;
		}
	}
	return false;
}
