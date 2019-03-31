// STfacedetection.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "STfacedetection.h"
#include <opencv2/face.hpp>
#include <opencv.hpp>

cv::CascadeClassifier g_cascade("./haarcascade_frontalface_alt");	// Ĭ�ϲ���haar��������
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

//��ǰ�ĸ�Mat���������Mat
bool ClassifierDetect(int rows, int cols, int type, void* data, 
	int flag, int minx, int miny, int maxx, int maxy) {
	if (g_cascade.empty() || !data || rows <= 0 || cols <= 0) return false;
	cv::Mat origin(rows, cols, type, data);
	cv::cvtColor(origin, g_gray, CV_BGR2GRAY);	// ת�Ҷ�ͼ
	cv::equalizeHist(g_gray, g_gray);	// ֱ��ͼ���⻯���򵥵���˵������߶Աȶ�
	g_cascade.detectMultiScale(g_gray, g_faceRect, 1.1f, 3, flag, cv::Size(minx, miny), cv::Size(maxx, maxy));
	return true;
}