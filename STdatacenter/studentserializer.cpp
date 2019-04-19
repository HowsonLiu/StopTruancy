#include "studentserializer.h"
#include "datacenter.h"
#include <QDir>
#include <QStringList>
#include <QTextStream>

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

void StudentSerializer::WriteImage(const std::vector<cv::Mat>& vm)
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

void StudentSerializer::ReadImages(std::vector<cv::Mat>* pvm)
{
	QDir dir(m_faceInfoPath);
	if (!pvm || !dir.exists()) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	for (QString imageName : imageNameList) {
		cv::String imagePath = dir.filePath(imageName).toStdString();
		pvm->push_back(cv::imread(imagePath, 0));	// 读入灰色图像
	}
}

std::vector<QString> StudentSerializer::Classes()
{
	std::vector<QString> res;
	QFile classesFile(m_cfgPath);
	if (classesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		while (!classesFile.atEnd()) {
			res.push_back(classesFile.readLine());
		}
	}
	classesFile.close();
	return res;
}

bool StudentSerializer::AddClass(const QString& name)
{
	QFile classesFile(m_cfgPath);
	QDir dir;
	if (!dir.exists(m_path)) dir.mkpath(m_path);
	if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) return false;
	QTextStream writer(&classesFile);
	writer << name << endl;
	classesFile.close();
	return false;
}

bool StudentSerializer::Delete()
{
	QFile file(m_cfgPath);
	if (file.exists() && file.size() > 0) return false;	// 有选修的课程时不可删除
	QDir dir(m_path);
	return dir.removeRecursively();
}
