// FaceDS.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FaceDS.h"
#include "DlibHeader.hpp"

anet_type gNet;
frontal_face_detector gDetector = get_frontal_face_detector();

FACE_DS_API void faceDS_init()
{
	deserialize("models/dlib_face_recognition_resnet_model_v1.dat") >> (gNet);
}