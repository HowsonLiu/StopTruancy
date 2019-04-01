#pragma once

extern "C" __declspec(dllexport) bool ClassifierEmpty();

extern "C" __declspec(dllexport) bool ClassifierLoadXml(const char*);

extern "C" __declspec(dllexport) void* GetVectorRect();

extern "C" __declspec(dllexport) bool ClassifierDetect(int rows, int cols, int type, void* data,
	int flag, int minx, int miny, int maxx, int maxy);

extern "C" __declspec(dllexport) bool ClassifierDetectEx(void* pMat, int flag, int minx, int miny, int maxx, int maxy);