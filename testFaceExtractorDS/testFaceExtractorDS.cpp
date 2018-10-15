// testFaceExtractorDS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../FaceDS/FaceDS.h"
#include "../FaceDS/FaceExtractorDS.h"
#include "../FaceDS/FaceComparetorDS.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	faceDS_init();
	FaceExtractorDS extractor;
	VFaceFeatureInfo vFaceFeatureInfo;
	int ret = extractor.extract(argv[1], vFaceFeatureInfo);
	auto it = vFaceFeatureInfo.begin();
	while (it != vFaceFeatureInfo.end())
	{
		int size = (*it).size / 4;
		float* feat = (float*)((*it).feat);
		for (int i = 0; i < size; i++)
		{
			cout << feat[i] << "\t";
		}
		cout << endl;
		it++;
	}
	//FaceComparetorDS cmp;
	//int ret = cmp.compare(argv[1], argv[2]);
    return 0;
}

