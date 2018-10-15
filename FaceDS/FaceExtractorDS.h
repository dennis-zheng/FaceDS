#ifndef _FACE_EXTRACTOR_DS_H_
#define _FACE_EXTRACTOR_DS_H_

#ifdef WIN64
#ifdef FACEDS_EXPORTS
#define FACE_EXTRACTOR_DS_API __declspec(dllexport) 
#else
#define FACE_EXTRACTOR_DS_API __declspec(dllimport) 
#endif
#else
#define FACE_EXTRACTOR_DS_API
#endif

#include "FaceHeader.h"

namespace dlib
{
	class shape_predictor;
}

class FACE_EXTRACTOR_DS_API FaceExtractorDS
{
public:
	FaceExtractorDS();
	~FaceExtractorDS();

public:
	int extract(const char* fileName, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect = false);
	int extract(const char* picBuf, const int size, VFaceFeatureInfo& vFaceFeatureInfo, bool isDetect = false);
private:	
	dlib::shape_predictor* sp_;
};

#endif // _FACE_EXTRACTOR_DS_H_