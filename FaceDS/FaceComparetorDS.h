#ifndef _FACE_COMPARETOR_DS_H_
#define _FACE_COMPARETOR_DS_H_

#ifdef WIN64
#ifdef FACEDS_EXPORTS
#define FACE_COMPARETOR_DS_API __declspec(dllexport) 
#else
#define FACE_COMPARETOR_DS_API __declspec(dllimport) 
#endif
#else
#define FACE_COMPARETOR_DS_API
#endif

#include "FaceHeader.h"

namespace dlib
{
	class shape_predictor;
}

class FACE_COMPARETOR_DS_API FaceComparetorDS
{
public:
	FaceComparetorDS();
	~FaceComparetorDS();

public:
	int compare(const char* fileName1, const char* fileName2);

private:
	dlib::shape_predictor* sp_;
};

#endif // _FACE_COMPARETOR_DS_H_