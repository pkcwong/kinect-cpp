#include "pk_kinect.h"

Kinect::Kinect()
{
	this->sensor = NULL;
	this->frame = NULL;
	this->reader = NULL;
	this->mapper = NULL;
	this->colorData = new BYTE[COLOR_HEIGHT * COLOR_WIDTH * 4];
	this->depthData = new USHORT[DEPTH_HEIGHT * DEPTH_WIDTH];
	this->irData = new USHORT[IR_HEIGHT, IR_WIDTH];
}

Kinect::~Kinect()
{
	if (this->sensor)
	{
		this->sensor->Close();
		this->sensor->Release();
		this->frame->Release();
		this->reader->Release();
		this->mapper->Release();
	}
	delete[] this->colorData;
	delete[] this->depthData;
	delete[] this->irData;
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
		IColorFrame* color = NULL;
		IDepthFrame* depth = NULL;
		IInfraredFrame* IR = NULL;
		IColorFrameReference* colorRef = NULL;
		IDepthFrameReference* depthRef = NULL;
		IInfraredFrameReference* IRRef = NULL;
		this->frame->get_ColorFrameReference(&colorRef);
		this->frame->get_DepthFrameReference(&depthRef);
		this->frame->get_InfraredFrameReference(&IRRef);
		if (SUCCEEDED(colorRef->AcquireFrame(&color)))
		{
			color->CopyConvertedFrameDataToArray(COLOR_WIDTH * COLOR_HEIGHT * 4, this->colorData, ColorImageFormat_Bgra);
			colorRef->Release();
			color->Release();
		}
		if (SUCCEEDED(depthRef->AcquireFrame(&depth)))
		{
			depth->CopyFrameDataToArray(DEPTH_WIDTH * DEPTH_HEIGHT, this->depthData);
			depthRef->Release();
			depth->Release();
		}
		/*
		if (SUCCEEDED(IRRef->AcquireFrame(&IR)))
		{
			IR->CopyFrameDataToArray(IR_WIDTH * IR_HEIGHT, this->irData);
			IRRef->Release();
			IR->Release();
		}
		*/
		return true;
	}
	return false;
}

BYTE* Kinect::getRgba()
{
	return this->colorData;
}

USHORT* Kinect::getDepth()
{
	return this->depthData;
}

USHORT* Kinect::getIr()
{
	return this->irData;
}
