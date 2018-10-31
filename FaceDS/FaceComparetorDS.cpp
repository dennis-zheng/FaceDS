#include "FaceComparetorDS.h"
#include "DlibHeader.hpp"

using namespace dlib;
using namespace std;

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

int FaceComparetorDS::compare(const char* feat1, const char* feat2)
{
	matrix<float, 0, 1>* face_descriptors1 = (matrix<float, 0, 1>*)feat1;
	matrix<float, 0, 1>* face_descriptors2 = (matrix<float, 0, 1>*)feat2;
	return length(*face_descriptors1 - *face_descriptors2) * 1000;
}

int FaceComparetorDS::compare(const char* feat1, const int size1, const char* feat2, const int size2)
{
	int size = size1 / 4;
	if (size != size2 / 4)
		return -1;
	float* f1 = (float*)feat1;
	float* f2 = (float*)feat2;
	matrix<float, 0, 1> face_descriptors1(size, 1);
	matrix<float, 0, 1> face_descriptors2(size, 1);
	for (int i = 0; i < size; i++)
	{
		face_descriptors1(i, 0) = f1[i];
		face_descriptors2(i, 0) = f2[i];
	}
	return compare((char*)&face_descriptors1,(char*)&face_descriptors2);
}