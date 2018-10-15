#include "FaceComparetorDS.h"
#include "DlibHeader.hpp"

FaceComparetorDS::FaceComparetorDS()
{
	//shape_predictor *sp_;
	sp_ = new shape_predictor;
	deserialize("models/shape_predictor_5_face_landmarks.dat") >> (*sp_);
	deserialize("models/dlib_face_recognition_resnet_model_v1.dat") >> (gNet);
}


FaceComparetorDS::~FaceComparetorDS()
{
}

int FaceComparetorDS::compare(const char* fileName1, const char* fileName2)
{
	matrix<rgb_pixel> img1;
	load_image(img1, fileName1);
	//pyramid_up(img);
	std::vector<matrix<rgb_pixel>> faces1;
	for (auto face : gDetector(img1))
	{
		auto shape = (*sp_)(img1, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);
		faces1.push_back(move(face_chip));
	}

	if (faces1.size() == 0)
	{
		return -1;
	}
	std::vector<matrix<float, 0, 1>> face_descriptors1 = gNet(faces1);
	

	matrix<rgb_pixel> img2;
	load_image(img2, fileName2);
	//pyramid_up(img);
	std::vector<matrix<rgb_pixel>> faces2;
	for (auto face : gDetector(img2))
	{
		auto shape = (*sp_)(img2, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img2, get_face_chip_details(shape, 150, 0.25), face_chip);
		faces2.push_back(move(face_chip));
	}

	if (faces2.size() == 0)
	{
		return -1;
	}
	std::vector<matrix<float, 0, 1>> face_descriptors2 = gNet(faces2);


	float score = length(face_descriptors1[0] - face_descriptors2[0]);
	cout << "score" << score << endl;
	return 0;
}