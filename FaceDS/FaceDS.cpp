// FaceDS.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace dlib;
using namespace std;

frontal_face_detector detector = get_frontal_face_detector();