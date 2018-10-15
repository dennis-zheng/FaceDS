#ifndef _FACE_HEADER_H_
#define _FACE_HEADER_H_
#include <string.h>
#include <vector>
struct FaceInfo
{
	int x;
	int y;
	int width;
	int height;
	int orient;
	int flag;

	FaceInfo()
	{
		memset(this, 0, sizeof(FaceInfo));
	}
};

struct FaceFeatureInfo
{
	char* feat;
	int size;
	FaceFeatureInfo()
	{
		memset(this, 0, sizeof(FaceFeatureInfo));
	}
};

typedef std::vector<FaceInfo> VFaceInfo;
typedef std::vector<FaceFeatureInfo> VFaceFeatureInfo;

#endif // _FACE_HEADER_H_