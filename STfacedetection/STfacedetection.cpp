// STfacedetection.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "STfacedetection.h"
#include <opencv2/face.hpp>
#include <opencv.hpp>

cv::CascadeClassifier g_cascade("./haarcascade_frontalface_alt");	// 默认采用haar的人脸集
std::vector<cv::Rect> g_faceRect;
cv::Mat g_gray;

bool ClassifierEmpty() {
	return g_cascade.empty();
}

bool ClassifierLoadXml(const char* xmlPath) {
	return g_cascade.load(xmlPath);
}

void* GetVectorRect() {
	return static_cast<void*>(&g_faceRect);
}

//用前四个Mat参数构造出Mat
bool ClassifierDetect(int rows, int cols, int type, void* data, 
	int flag, int minx, int miny, int maxx, int maxy) {
	if (g_cascade.empty() || !data || rows <= 0 || cols <= 0) return false;
	cv::Mat origin(rows, cols, type, data);
	cv::cvtColor(origin, g_gray, CV_BGR2GRAY);	// 转灰度图
	cv::equalizeHist(g_gray, g_gray);	// 直方图均衡化，简单点来说就是提高对比度
	g_cascade.detectMultiScale(g_gray, g_faceRect, 1.1f, 3, flag, cv::Size(minx, miny), cv::Size(maxx, maxy));
	return true;
}