#ifndef _FACE_DETECTOR_DS_H_
#define _FACE_DETECTOR_DS_H_

#ifdef WIN64
#ifdef FACEDS_EXPORTS
#define FACE_DETECTOR_DS_API __declspec(dllexport) 
#else
#define FACE_DETECTOR_DS_API __declspec(dllimport) 
#endif
#else
#define FACE_DETECTOR_DS_API
#endif

#include "FaceHeader.h"

class FACE_DETECTOR_DS_API FaceDetectorDS
{
public:
	FaceDetectorDS();
	~FaceDetectorDS();

public:
	// fileName: picture file path
	int detect(const char* fileName, VFaceInfo& vFaceInfo);

	// picBuf: picture buffer
	int detect(const char* picBuf, const int size, VFaceInfo& vFaceInfo);

private:
	
};

#endif // _FACE_DETECTOR_DS_H_