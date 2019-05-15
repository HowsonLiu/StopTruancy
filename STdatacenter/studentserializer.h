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
	bool exists() const;
	bool canDelete() const;
	bool init();
	void writeImage(const cv::Mat&);
	void writeImages(const std::vector<cv::Mat>&);
	void readOriginImages(std::vector<cv::Mat>*);
	void readTrainImages(std::vector<cv::Mat>*);
	void readProfilePhoto(QPixmap*);
	std::vector<QString> classes();
	bool addClass(const QString&);
	bool delClass(const QString&);
	bool deletes();
};

