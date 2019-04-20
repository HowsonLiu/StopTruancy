#pragma once
#include <QString>
#include <opencv2/opencv.hpp>

#define DEFAULT_SUFFIX ".jpg"

class StudentSerializer
{
private:
	const QString m_name;
	const QString m_path;
	const QString m_faceInfoPath;
	const QString m_cfgPath;

public:
	StudentSerializer(const QString&);
	~StudentSerializer();
	void WriteImage(const std::vector<cv::Mat>&);
	void ReadImages(std::vector<cv::Mat>*);
	std::vector<QString> Classes();
	bool AddClass(const QString&);
	bool Init();
	bool Delete();
};

