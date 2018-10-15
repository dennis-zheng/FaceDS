// testFaceDetectorDS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../FaceDS/FaceDetectorDS.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	FaceDetectorDS detector;
	VFaceInfo vFaceInfo;
	int ret = detector.detect(argv[1], vFaceInfo);

	auto it = vFaceInfo.begin();
	while (it != vFaceInfo.end())
	{
		cout << it->x << "\t" << it->y << "\t" << it->width << "\t" << it->height << endl;
		it++;
	}
	cout << vFaceInfo.size() << endl;
    return 0;
}

