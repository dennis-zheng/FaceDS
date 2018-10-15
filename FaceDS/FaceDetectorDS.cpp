#include "FaceDetectorDS.h"
#include "DlibHeader.hpp"

FaceDetectorDS::FaceDetectorDS()
{
}

FaceDetectorDS::~FaceDetectorDS()
{
}

int FaceDetectorDS::detect(const char* fileName, VFaceInfo& vFaceInfo)
{
	matrix<rgb_pixel> img;
	load_image(img, fileName);
	//pyramid_up(img);
	std::vector<rectangle> dets = gDetector(img);
	auto it = dets.begin();
	while(it != dets.end())
	{
		FaceInfo info;
		info.x = it->left();
		info.y = it->top();
		info.width = it->width();
		info.height = it->height();
		vFaceInfo.push_back(info);
		it++;
	}
	return dets.size();
}

int FaceDetectorDS::detect(const char* picBuf, const int size, VFaceInfo& vFaceInfo)
{
	matrix<rgb_pixel> img;
	//load_image(img, fileName);
	//pyramid_up(img);
	std::vector<rectangle> dets = gDetector(img);
	auto it = dets.begin();
	while (it != dets.end())
	{
		FaceInfo info;
		info.x = it->left();
		info.y = it->top();
		info.width = it->width();
		info.height = it->height();
		vFaceInfo.push_back(info);
		it++;
	}
	return dets.size();
}