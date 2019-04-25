#pragma once
#include <QString>
#include <opencv2/opencv.hpp>

#define DEFAULT_SUFFIX ".jpg"

#define TRAIN_RESIZE_WIDTH 92
#define TRAIN_RESIZE_HEIGHT 112

class QPixmap;
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
	bool canDelete() const;
	bool Init();
	void WriteImages(const std::vector<cv::Mat>&);
	void ReadOriginImages(std::vector<cv::Mat>*);
	void ReadTrainImages(std::vector<cv::Mat>*);
	void ReadProfilePhoto(QPixmap*);
	std::vector<QString> Classes();
	bool AddClass(const QString&);
	bool DelClass(const QString&);
	bool Delete();
};

