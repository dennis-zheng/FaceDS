// testFaceExtractorDS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../FaceDS/FaceDS.h"
#include "../FaceDS/FaceDetectorDS.h"
#include "../FaceDS/FaceExtractorDS.h"
#include "../FaceDS/FaceComparetorDS.h"
#include <iostream>
using namespace std;

int detectTest(int argc, char* argv[])
{
	FaceDetectorDS detector;
	VFaceInfo vFaceInfo;
	int ret = detector.detect(argv[2], vFaceInfo);

	auto it = vFaceInfo.begin();
	while (it != vFaceInfo.end())
	{
		cout << (*it)->x << "\t" << (*it)->y << "\t" << (*it)->width << "\t" << (*it)->height << endl;
		delete *it;
		it++;
	}
	cout << vFaceInfo.size() << endl;
	return 0;
}

int extractTest(int argc, char* argv[])
{
	FaceExtractorDS extractor;
	VFaceFeatureInfo vFaceFeatureInfo;
	cout << __FUNCTION__ << " 00 " << endl;
	char* buf = new char[1024 * 1024];
	FILE* fpr = NULL;
	fopen_s(&fpr, argv[2], "rb");
	int rd = fread(buf, 1, 1024 * 1024, fpr);
	cout << __FUNCTION__ << " rd " << rd << endl;
	fclose(fpr);
	int ret = extractor.extractByBuf(buf, rd, vFaceFeatureInfo, true);
	//int ret = extractor.extractByFile(argv[2], vFaceFeatureInfo, true);
	cout << __FUNCTION__ << " 11 " << endl;
	auto it = vFaceFeatureInfo.begin();
	int index = 0;
	while (it != vFaceFeatureInfo.end())
	{
		cout << __FUNCTION__ << " 22 " << (*it)->size << endl;
		char path[256];
		sprintf_s(path, 256, "%s_%d.bin", argv[2], index);
		FILE* fp = NULL;
		fopen_s(&fp, path, "wb");
		fwrite((*it)->feat, 1, (*it)->size, fp);
		fclose(fp);
		delete *it;
		it++;
		index++;
	}
	cout << __FUNCTION__ << " 55 " << endl;
	return 0;
}

int compareTest(int argc, char* argv[])
{
	char* feat1 = new char[128 * 4];
	char* feat2 = new char[128 * 4];

	FILE* fp = NULL;
	fopen_s(&fp, argv[2], "rb");
	int rd = fread(feat1, 1, 1024, fp);
	cout << __FUNCTION__ << " rd " << rd << endl;
	fclose(fp);
	fp = NULL;
	fopen_s(&fp, argv[3], "rb");
	rd = fread(feat2, 1, 1024, fp);
	cout << __FUNCTION__ << " rd " << rd << endl;
	fclose(fp);

	FaceComparetorDS comparetor;
	int score = comparetor.compare(feat1, rd, feat2, rd);
	cout << __FUNCTION__ << " score " << score << endl;
	return 0;
}

int main(int argc, char* argv[])
{
	faceDS_init();
	int type = atoi(argv[1]);
	if(type == 0)
		detectTest(argc, argv);
	else if (type == 1)
		extractTest(argc, argv);
	else
		compareTest(argc, argv);
    return 0;
}

