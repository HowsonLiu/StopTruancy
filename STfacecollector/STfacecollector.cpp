// STfacecollector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "STfacedetection.lib")
extern "C" __declspec(dllexport) bool ClassifierEmpty();
extern "C" __declspec(dllexport) bool ClassifierLoadXml(const char*);
extern "C" __declspec(dllexport) void* GetVectorRect();
extern "C" __declspec(dllexport) bool ClassifierDetect(int rows, int cols, int type, void* data,
	int flag, int minx, int miny, int maxx, int maxy);

int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened()) return -1;
	std::vector<cv::Rect>* pFaceRectVec;
	if (!ClassifierEmpty()) return -1;
	cv::Mat frame;
	while (true) {
		cap >> frame;
		cv::imshow("face collector", frame);
		cv::waitKey(30);
		ClassifierDetect(frame.rows, frame.cols, frame.type(), frame.data, CV_HAAR_SCALE_IMAGE, 100, 100, 600, 600);
		pFaceRectVec = static_cast<std::vector<cv::Rect>*> (GetVectorRect());
		if (pFaceRectVec) {
			std::cout << pFaceRectVec->size() << std::endl;
			if(pFaceRectVec->size() > 0) break;
		}
	}
	return 0;
}