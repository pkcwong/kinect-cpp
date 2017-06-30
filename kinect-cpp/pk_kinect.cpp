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
	if (this->sensor)
	{
		IColorFrameSource* framesource = NULL;
		if (SUCCEEDED(hr))
		{
			hr = this->sensor->Open();
		}
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

bool Kinect::fetchRGBA(GLubyte* buffer)
{
	IColorFrame* colorframe = NULL;
	HRESULT hr;
	if (!this->reader)
	{
		return false;
	}
	hr = this->reader->AcquireLatestFrame(&colorframe);
	if (FAILED(hr))
	{
		return false;
	}
	colorframe->CopyConvertedFrameDataToArray(WIDTH * HEIGHT * 4, buffer, ColorImageFormat_Bgra);
	colorframe->Release();
	return true;
}
