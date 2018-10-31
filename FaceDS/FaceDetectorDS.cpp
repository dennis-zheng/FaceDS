#include "FaceDetectorDS.h"
#include "DlibHeader.hpp"
#include "opencv2\opencv.hpp"

using namespace dlib;
using namespace std;

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
	std::vector<char> data;
	for (int i = 0; i < size; i++)
		data.push_back(picBuf[i]);
	cv::Mat frame = cv::imdecode(cv::Mat(data), 1);
	matrix<rgb_pixel> img;
	assign_image(img, cv_image<rgb_pixel>(frame));
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