#pragma once
#include <QString>
#include <opencv2/opencv.hpp>

#define DEFAULT_SUFFIX ".jpg"

class StudentSerializer
{
private:
	const QString m_name;
	const QString m_path;		// ��·���Ƿ���ھ���ѧ���Ƿ����
	const QString m_faceInfoPath;
	const QString m_cfgPath;	// cfg�ļ���û��ֵ����ѧ���ܷ�ɾ��

public:
	StudentSerializer(const QString&);
	~StudentSerializer();
	bool Exist() const;
	bool Init();
	void WriteImage(const std::vector<cv::Mat>&);
	void ReadImages(std::vector<cv::Mat>*);
	void ReadProfilePhoto(cv::Mat*);
	std::vector<QString> Classes();
	bool AddClass(const QString&);
	bool DelClass(const QString&);
	bool Delete();
};

