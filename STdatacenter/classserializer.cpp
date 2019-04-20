#include "classserializer.h"
#include "datacenter.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

ClassSerializer::ClassSerializer(const QString& name)
	: m_name(name)
	, m_path(DATA_CENTER_INSTANCE->getClassPath() + "\\" + name)
	, m_lessonPath(m_path + "\\lesson")
	, m_xmlPath(m_path + QString("\\%1.xml").arg(name))
	, m_cfgPath(m_path + QString("\\%1.cfg").arg(name))
	, m_dbPath(m_path + QString("\\%1.db").arg(name))
{
}


ClassSerializer::~ClassSerializer()
{
}

bool ClassSerializer::Init()
{
	DATA_CENTER_INSTANCE->addClassName(m_name);
	QDir dir;
	if (!dir.exists(m_path)) return dir.mkpath(m_path);
	return true;
}

bool ClassSerializer::Exist() const
{
	return QDir(m_path).exists();
}

bool ClassSerializer::Delete()
{
	DATA_CENTER_INSTANCE->delClassName(m_name);
	QDir dir(m_path);
	return dir.removeRecursively();
}

bool ClassSerializer::AddStudent(const QString& name)
{
	QFile file(m_cfgPath);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&file);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// 去重
	}
	stream << name << endl;
	file.close();
	return true;
}

bool ClassSerializer::AddStudents(const std::vector<QString>& names)
{
	QFile file(m_cfgPath);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&file);
	std::vector<QString> tmp(names);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		std::vector<QString>::iterator it = std::find(tmp.begin(), tmp.end(), curStudent);
		while (it != tmp.end()) {
			tmp.erase(it);
			it = std::find(tmp.begin(), tmp.end(), curStudent);	// 去重
		}
	}
	for(QString name : tmp)
		stream << name << endl;
	file.close();
	return true;
}
