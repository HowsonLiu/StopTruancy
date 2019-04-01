// STfacecollector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "STfacedetection.lib")
extern "C" __declspec(dllimport) bool ClassifierEmpty();
extern "C" __declspec(dllimport) bool ClassifierLoadXml(const char*);
extern "C" __declspec(dllimport) void* GetVectorRect();
extern "C" __declspec(dllimport) bool ClassifierDetect(int rows, int cols, int type, void* data,
	int flag, int minx, int miny, int maxx, int maxy);
extern "C" __declspec(dllimport) bool ClassifierDetectEx(void* pMat, int flag, int minx, int miny, int maxx, int maxy);

int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened()) return -1;
	std::vector<cv::Rect>* pFaceRectVec;
	if (ClassifierEmpty()) {
		if(!ClassifierLoadXml("D:\\Programming_Project\\OpenCV\\StopTruancy\\x64\\Debug\\haarcascade_frontalface_alt.xml"))
			return -1;
	}
	cv::Mat frame;
	while (true) {
		cap >> frame;
		cv::imshow("face collector", frame);
		cv::waitKey(30);
		// bool res = ClassifierDetect(frame.rows, frame.cols, frame.type(), frame.data, CV_HAAR_SCALE_IMAGE, 100, 100, 600, 600);
		bool res = ClassifierDetectEx((void*)&frame, CV_HAAR_SCALE_IMAGE, 100, 100, 600, 600);
		pFaceRectVec = static_cast<std::vector<cv::Rect>*> (GetVectorRect());
		if (pFaceRectVec) {
			std::cout << pFaceRectVec->size() << " " << res << std::endl;
			if(pFaceRectVec->size() > 0) break;
		}
	}
	return 0;
}