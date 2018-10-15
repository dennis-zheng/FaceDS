#ifndef _FACE_DS_H_
#define __FACE_DS_H_

#ifdef WIN64
#ifdef FACEDS_EXPORTS
#define FACE_DS_API extern "C" __declspec(dllexport) 
#else
#define FACE_DS_API extern "C" __declspec(dllimport) 
#endif
#else
#define FACE_DS_API
#endif

FACE_DS_API void faceDS_init();

#endif // __FACE_DS_H_
