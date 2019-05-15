#include "studentserializer.h"
#include "datacenter.h"
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QPixmap>

StudentSerializer::StudentSerializer(const QString& name) 
	: m_name(name)
	, m_path(DATA_CENTER_INSTANCE->getStudentPath() + "\\" + name)
	, m_faceInfoPath(m_path + "\\face_information")
	, m_cfgPath(m_path + QString("\\%1.cfg").arg(name))
{
}

StudentSerializer::~StudentSerializer()
{
}

void StudentSerializer::writeImages(const std::vector<cv::Mat>& vm)
{
	QDir dir(m_faceInfoPath);
	if (!dir.exists() && !dir.mkpath(m_faceInfoPath)) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	int nameIndex = imageNameList.size();
	for (auto mat : vm) {
		QString name = m_faceInfoPath + QString("\\%1.jpg").arg(QString::number(nameIndex++));
		cv::imwrite(name.toStdString(), mat);
	}
}

void StudentSerializer::readOriginImages(std::vector<cv::Mat>* pvm)
{
	QDir dir(m_faceInfoPath);
	if (!pvm || !dir.exists()) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	for (QString imageName : imageNameList) {
		cv::String imagePath = dir.filePath(imageName).toStdString();
		pvm->push_back(cv::imread(imagePath));
	}
}

void StudentSerializer::readTrainImages(std::vector<cv::Mat>* pvm)
{
	QDir dir(m_faceInfoPath);
	if (!pvm || !dir.exists()) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	for (QString imageName : imageNameList) {
		cv::String imagePath = dir.filePath(imageName).toStdString();
		cv::Mat grayMat = cv::imread(imagePath, 0);		// 读入灰色图像
		cv::resize(grayMat, grayMat, cv::Size(TRAIN_RESIZE_WIDTH, TRAIN_RESIZE_HEIGHT));	// 不同规格训练会错
		pvm->push_back(grayMat.clone());	
	}
}

void StudentSerializer::readProfilePhoto(QPixmap* image)
{
	QDir dir(m_faceInfoPath);
	if (!image || !dir.exists()) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	if (imageNameList.isEmpty()) return;
	image->load(dir.filePath(imageNameList[0]));
}

std::vector<QString> StudentSerializer::classes()
{
	std::vector<QString> res;
	QFile classesFile(m_cfgPath);
	if (classesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&classesFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	classesFile.close();
	return res;
}

bool StudentSerializer::addClass(const QString& name)
{
	QFile classesFile(m_cfgPath);
	if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&classesFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// 去重
	}
	stream << name << endl;
	classesFile.close();
	return true;
}

bool StudentSerializer::delClass(const QString& name)
{
	std::vector<QString> Classes;
	QFile classesFile(m_cfgPath);
	if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&classesFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) != 0)
			Classes.push_back(curStudent);
	}
	classesFile.resize(0);	// 归零重写
	for (QString curStudent : Classes) {
		stream << curStudent << endl;
	}
	classesFile.close();
	return true;
}

bool StudentSerializer::init()
{
	QDir dir;
	if (dir.exists(m_path) || dir.mkpath(m_path) && dir.mkpath(m_faceInfoPath)) {
		DATA_CENTER_INSTANCE->addStudentName(m_name);
		return true;
	}
	return false;
}

void StudentSerializer::writeImage(const cv::Mat& mat)
{
	QDir dir(m_faceInfoPath);
	if (!dir.exists() && !dir.mkpath(m_faceInfoPath)) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	int nameIndex = imageNameList.size();
	QString name = m_faceInfoPath + QString("\\%1.jpg").arg(QString::number(nameIndex));
	cv::imwrite(name.toStdString(), mat);
}

bool StudentSerializer::deletes()
{
	DATA_CENTER_INSTANCE->delStudentName(m_name);
	QDir dir(m_path);
	return dir.removeRecursively();
}

bool StudentSerializer::exists() const
{
	return QDir(m_path).exists();
}

bool StudentSerializer::canDelete() const
{
	QFile file(m_cfgPath);
	return !file.exists() || file.size() <= 0;	// 有选修的课程时不可删除
}
