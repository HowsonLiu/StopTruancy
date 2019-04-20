#pragma once
#include <QString>
#include <opencv2/opencv.hpp>

#define DEFAULT_SUFFIX ".jpg"

class StudentSerializer
{
private:
	const QString m_name;
	const QString m_path;		// 此路径是否存在决定学生是否存在
	const QString m_faceInfoPath;
	const QString m_cfgPath;	// cfg文件有没有值决定学生能否删除

public:
	StudentSerializer(const QString&);
	~StudentSerializer();
	void WriteImage(const std::vector<cv::Mat>&);
	void ReadImages(std::vector<cv::Mat>*);
	std::vector<QString> Classes();
	bool AddClass(const QString&);
	bool DelClass(const QString&);
	bool Init();
	bool Delete();
	bool Exist() const;
};

