#include "pk_kinect.h"

namespace kinect
{

	IKinectSensor* sensor = NULL;
	IMultiSourceFrame* frame = NULL;
	IMultiSourceFrameReader* reader = NULL;
	ICoordinateMapper* mapper = NULL;
	BYTE* colorData = NULL;
	USHORT* depthData = NULL;
	USHORT* irData = NULL;

	bool initialize()
	{
		kinect::colorData = new BYTE[COLOR_HEIGHT * COLOR_WIDTH * 4];
		kinect::depthData = new USHORT[DEPTH_HEIGHT * DEPTH_WIDTH];
		kinect::irData = new USHORT[IR_HEIGHT * IR_WIDTH];
		if (SUCCEEDED(GetDefaultKinectSensor(&kinect::sensor)))
		{
			kinect::sensor->get_CoordinateMapper(&kinect::mapper);
			kinect::sensor->Open();
			kinect::sensor->OpenMultiSourceFrameReader(FrameSourceTypes::FrameSourceTypes_Depth | FrameSourceTypes::FrameSourceTypes_Color | FrameSourceTypes_Infrared, &kinect::reader);
			return true;
		}
		return false;
	}

	void close()
	{
		if (kinect::sensor)
		{
			kinect::sensor->Close();
			kinect::sensor->Release();
			kinect::frame->Release();
			kinect::reader->Release();
			kinect::mapper->Release();
		}
		delete[] kinect::colorData;
		delete[] kinect::depthData;
		delete[] kinect::irData;
	}

	bool fetch()
	{
		if (SUCCEEDED(kinect::reader->AcquireLatestFrame(&kinect::frame)))
		{
			IColorFrame* color = NULL;
			IDepthFrame* depth = NULL;
			IInfraredFrame* IR = NULL;
			IColorFrameReference* colorRef = NULL;
			IDepthFrameReference* depthRef = NULL;
			IInfraredFrameReference* IRRef = NULL;
			kinect::frame->get_ColorFrameReference(&colorRef);
			kinect::frame->get_DepthFrameReference(&depthRef);
			kinect::frame->get_InfraredFrameReference(&IRRef);
			if (SUCCEEDED(colorRef->AcquireFrame(&color)))
			{
				color->CopyConvertedFrameDataToArray(COLOR_WIDTH * COLOR_HEIGHT * 4, kinect::colorData, ColorImageFormat_Bgra);
				colorRef->Release();
				color->Release();
			}
			if (SUCCEEDED(depthRef->AcquireFrame(&depth)))
			{
				depth->CopyFrameDataToArray(DEPTH_WIDTH * DEPTH_HEIGHT, kinect::depthData);
				depthRef->Release();
				depth->Release();
			}
			if (SUCCEEDED(IRRef->AcquireFrame(&IR)))
			{
				IR->CopyFrameDataToArray(IR_WIDTH * IR_HEIGHT, kinect::irData);
				IRRef->Release();
				IR->Release();
			}
			return true;
		}
		return false;
	}

	BYTE* getRgba()
	{
		return kinect::colorData;
	}

	USHORT* getDepth()
	{
		return kinect::depthData;
	}

	USHORT* getIr()
	{
		return kinect::irData;
	}

}
