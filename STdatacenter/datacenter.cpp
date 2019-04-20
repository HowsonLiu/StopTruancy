#include "datacenter.h"
#include <QFile>
#include <QTextStream>

DataCenter::DataCenter()
	: m_rootPath(ROOT_PATH)
	, m_allClassStcPath(m_rootPath + "\\class.stc")
	, m_allStudentStsPath(m_rootPath + "\\student.sts")
	, m_classPath(m_rootPath + "\\class")
	, m_studentPath(m_rootPath + "\\student")
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
	return m_classPath;
}

QString DataCenter::getStudentPath() const
{
	return m_studentPath;
}

std::vector<QString> DataCenter::getAllClassName() const
{
	std::vector<QString> res;
	QFile allClassFile(m_allClassStcPath);
	if (allClassFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&allClassFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	allClassFile.close();
	return res;
}

bool DataCenter::addClassName(const QString& name)
{
	QFile allClassFile(m_allClassStcPath);
	if (!allClassFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&allClassFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// 去重
	}
	stream << name << endl;
	allClassFile.close();
	return false;
}

bool DataCenter::delClassName(const QString& name)
{
	std::vector<QString> allClasses;
	QFile allClassFile(m_allClassStcPath);
	if (!allClassFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&allClassFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if(QString::compare(name, curStudent) != 0)
			allClasses.push_back(curStudent);
	}
	allClassFile.resize(0);	// 归零重写
	for (QString curStudent : allClasses) {
		stream << curStudent << endl;
	}
	allClassFile.close();
	return true;
}

std::vector<QString> DataCenter::getAllStudentName() const
{
	std::vector<QString> res;
	QFile allStudentFile(m_allStudentStsPath);
	if (allStudentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&allStudentFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	allStudentFile.close();
	return res;
}

bool DataCenter::addStudentName(const QString &name)
{
	QFile allStudentFile(m_allStudentStsPath);
	if (!allStudentFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&allStudentFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// 去重
	}
	stream << name << endl;
	allStudentFile.close();
	return false;
}

bool DataCenter::delStudentName(const QString & name)
{
	std::vector<QString> allStudents;
	QFile allStudentFile(m_allStudentStsPath);
	if (!allStudentFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&allStudentFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) != 0)
			allStudents.push_back(curStudent);
	}
	allStudentFile.resize(0);	// 归零重写
	for (QString curStudent : allStudents) {
		stream << curStudent << endl;
	}
	allStudentFile.close();
	return true;
}
