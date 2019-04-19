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
		while (!allClassFile.atEnd()) {
			res.push_back(allClassFile.readLine());
		}
	}
	allClassFile.close();
	return res;
}

bool DataCenter::addClassName(const QString& name)
{
	QFile allClassFile(m_allClassStcPath);
	if (!allClassFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) return false;
	QTextStream writer(&allClassFile);
	writer << name << endl;
	allClassFile.close();
	return false;
}

std::vector<QString> DataCenter::getAllStudentName() const
{
	std::vector<QString> res;
	QFile allStudentFile(m_allStudentStsPath);
	if (allStudentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		while (!allStudentFile.atEnd()) {
			res.push_back(allStudentFile.readLine());
		}
	}
	allStudentFile.close();
	return res;
}

bool DataCenter::addStudentName(const QString &name)
{
	QFile allStudentFile(m_allStudentStsPath);
	if (!allStudentFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) return false;
	QTextStream writer(&allStudentFile);
	writer << name << endl;
	allStudentFile.close();
	return false;
}
