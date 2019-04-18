#include "datacenter.h"
#include <QFile>
#include <QTextStream>

DataCenter::DataCenter() 
	: m_rootPath(ROOT_PATH)
	, m_allClassPath(m_rootPath + "\\class.stc")
	, m_allStudentPath(m_rootPath + "\\student.sts")
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

std::vector<QString> DataCenter::getAllClassName() const
{
	std::vector<QString> res;
	QFile allClassFile(m_allClassPath);
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
	QFile allClassFile(m_allClassPath);
	if (!allClassFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) return false;
	QTextStream writer(&allClassFile);
	writer << name << endl;
	allClassFile.close();
	return false;
}

std::vector<QString> DataCenter::getAllStudentName() const
{
	std::vector<QString> res;
	QFile allStudentFile(m_allStudentPath);
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
	QFile allStudentFile(m_allStudentPath);
	if (!allStudentFile.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) return false;
	QTextStream writer(&allStudentFile);
	writer << name << endl;
	allStudentFile.close();
	return false;
}
