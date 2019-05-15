#include "datacenter.h"
#include <QFile>
#include <QTextStream>

DataCenter::DataCenter()
	: m_rootPath(ROOT_PATH)
	, m_classesCacheStcPath(m_rootPath + "\\class.stc")
	, m_studentsCacheStsPath(m_rootPath + "\\student.sts")
	, m_classesFolderPath(m_rootPath + "\\class")
	, m_studentsFolderPath(m_rootPath + "\\student")
	, m_faceDetectionXmlPath(m_rootPath + "\\face_detection.xml")
{
}


DataCenter::~DataCenter()
{
}

DataCenter * DataCenter::getInstance()
{
	static DataCenter instance;
	return &instance;
}

QString DataCenter::getRootPath() const
{
	return m_rootPath;
}

QString DataCenter::getClassPath() const
{
	return m_classesFolderPath;
}

QString DataCenter::getStudentPath() const
{
	return m_studentsFolderPath;
}

QString DataCenter::getFaceDetectionXmlPath() const
{
	return m_faceDetectionXmlPath;
}

std::vector<QString> DataCenter::getAllClassName() const
{
	std::vector<QString> res;
	QFile classesCacheFile(m_classesCacheStcPath);
	if (classesCacheFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&classesCacheFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	classesCacheFile.close();
	return res;
}

bool DataCenter::addClassName(const QString& name)
{
	QFile classesCacheFile(m_classesCacheStcPath);
	if (!classesCacheFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&classesCacheFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// 去重
	}
	stream << name << endl;
	classesCacheFile.close();
	return true;
}

bool DataCenter::delClassName(const QString& name)
{
	std::vector<QString> allClasses;
	QFile classesCacheFile(m_classesCacheStcPath);
	if (!classesCacheFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&classesCacheFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if(QString::compare(name, curStudent) != 0)
			allClasses.push_back(curStudent);
	}
	classesCacheFile.resize(0);	// 归零重写
	for (QString curStudent : allClasses) {
		stream << curStudent << endl;
	}
	classesCacheFile.close();
	return true;
}

std::vector<QString> DataCenter::getAllStudentName() const
{
	std::vector<QString> res;
	QFile studentsCacheFile(m_studentsCacheStsPath);
	if (studentsCacheFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&studentsCacheFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	studentsCacheFile.close();
	return res;
}

bool DataCenter::addStudentName(const QString &name)
{
	QFile studentsCacheFile(m_studentsCacheStsPath);
	if (!studentsCacheFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&studentsCacheFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// 去重
	}
	stream << name << endl;
	studentsCacheFile.close();
	return false;
}

bool DataCenter::delStudentName(const QString & name)
{
	std::vector<QString> allStudents;
	QFile studentsCacheFile(m_studentsCacheStsPath);
	if (!studentsCacheFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&studentsCacheFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) != 0)
			allStudents.push_back(curStudent);
	}
	studentsCacheFile.resize(0);	// 归零重写
	for (QString curStudent : allStudents) {
		stream << curStudent << endl;
	}
	studentsCacheFile.close();
	return true;
}
