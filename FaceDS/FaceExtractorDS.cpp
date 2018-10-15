#include "FaceExtractorDS.h"
#include "dlibHeader.hpp"

FaceExtractorDS::FaceExtractorDS()
{
	sp_ = new shape_predictor;
	deserialize("models/shape_predictor_5_face_landmarks.dat") >> (*sp_);
}

FaceExtractorDS::~FaceExtractorDS()
{
}

int FaceExtractorDS::extract(const char* fileName, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect/* = false*/)
{
	matrix<rgb_pixel> img;
	load_image(img, fileName);
	//pyramid_up(img);
	std::vector<matrix<rgb_pixel>> faces;
	if (isDetect)
	{
		for (auto face : gDetector(img))
		{
			auto shape = (*sp_)(img, face);
			matrix<rgb_pixel> face_chip;
			extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
			faces.push_back(move(face_chip));
		}
	}
	else
	{
		rectangle face;
		auto shape = (*sp_)(img, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
		faces.push_back(move(face_chip));
	}
	
	if (faces.size() == 0)
	{
		return -1;
	}

	std::vector<matrix<float, 0, 1>> face_descriptors = gNet(faces, 16);
	//auto xx = trans(face_descriptors[0]);
	auto it = face_descriptors.begin();
	while (it != face_descriptors.end())
	{
		FaceFeatureInfo info;
		int size = (*it).size();
		info.size = size * 4;
		info.feat = new char[info.size];
		float* feat = (float*)info.feat;
		for (int i = 0; i < size; i++)
		{
			feat[i] = face_descriptors[0](0, i);
			//cout << feat[i] << "\t";
		}
		//cout << endl;
		it++;
		vFaceFeatureInfo.push_back(info);
	}
	return 0;
}

int FaceExtractorDS::extract(const char* picBuf, const int size, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect/* = false*/)
{
	return 0;
}