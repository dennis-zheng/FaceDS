#include "FaceExtractorDS.h"
#include "dlibHeader.hpp"
#include "opencv2\opencv.hpp"

using namespace dlib;
using namespace std;

FaceExtractorDS::FaceExtractorDS()
{
	sp_ = new shape_predictor;
	deserialize("models/shape_predictor_5_face_landmarks.dat") >> (*sp_);
}

FaceExtractorDS::~FaceExtractorDS()
{
}

int FaceExtractorDS::extract(const char* img, char* feature, bool isDetect/* = false*/)
{
	std::vector<matrix<float, 0, 1>>* featureMat = (std::vector<matrix<float, 0, 1>>*)feature;
	matrix<rgb_pixel>* imgT = (matrix<rgb_pixel>*)img;
	//pyramid_up(*imgT);
	std::vector<matrix<rgb_pixel>> faces;
	if (isDetect)
	{
		for (auto face : gDetector(*imgT))
		{
			auto shape = (*sp_)(*imgT, face);
			matrix<rgb_pixel> face_chip;
			extract_image_chip(*imgT, get_face_chip_details(shape, 150, 0.25), face_chip);
			faces.push_back(move(face_chip));
		}
	}
	else
	{
		rectangle face;
		auto shape = (*sp_)(*imgT, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(*imgT, get_face_chip_details(shape, 150, 0.25), face_chip);
		faces.push_back(move(face_chip));
	}

	if (faces.size() == 0)
	{
		return -1;
	}
	std::vector<matrix<float, 0, 1>> face_descriptors = gNet(faces, 16);
	//std::vector<matrix<float, 0, 1>> face_descriptors = gNet(faces, 16);
	//auto xx = trans(face_descriptors[0]);
	featureMat->assign(face_descriptors.begin(), face_descriptors.end());
	return 0;
}

int FaceExtractorDS::extract(const char* img, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect/* = false*/)
{
	std::vector<matrix<float, 0, 1>> face_descriptors;
	extract(img, (char*)&face_descriptors, isDetect);
	auto it = face_descriptors.begin();
	while (it != face_descriptors.end())
	{
		FaceFeatureInfo* info = new FaceFeatureInfo;
		int size = (*it).size();
		info->size = size * 4;
		info->feat = new char[info->size];
		float* feat = (float*)info->feat;
		memset(feat, 0, size);
		for (int i = 0; i < size; i++)
		{
			feat[i] = (*it)(0, i);
			//cout << feat[i] << "\t";
		}
		//cout << endl;
		it++;
		vFaceFeatureInfo.push_back(info);
	}
	return 0;
}

int FaceExtractorDS::extractByFile(const char* fileName, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect/* = false*/)
{
	matrix<rgb_pixel> img;
	load_image(img, fileName);
	return extract((char*)&img, vFaceFeatureInfo, isDetect);
}

int FaceExtractorDS::extractByBuf(const char* picBuf, const int size, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect/* = false*/)
{
	std::vector<char> data;
	for (int i = 0; i < size; i++)
		data.push_back(picBuf[i]);
	cv::Mat frame = cv::imdecode(cv::Mat(data), 1);
	matrix<rgb_pixel> img;
	assign_image(img, cv_image<rgb_pixel>(frame));
	// 效率有待提升
	int sizeI = img.size();
	for (int i = 0; i < sizeI; i++)
	{
		rgb_pixel bgr = img(i);
		rgb_pixel tmp(bgr.blue, bgr.green, bgr.red);
		img(i) = tmp;
	}
	return extract((char*)&img, vFaceFeatureInfo, isDetect);
}
