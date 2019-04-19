#pragma once
#include <QString>
#include <vector>

#define ROOT_PATH "D:\\tmp\\data"

class DataCenter
{
private:
	const QString m_rootPath;
	const QString m_allClassStcPath;
	const QString m_allStudentStsPath;
	const QString m_classPath;
	const QString m_studentPath;

private:
	DataCenter();
	~DataCenter();

public:
	static DataCenter* getInstance();
	QString getRootPath() const;
	QString getClassPath() const;
	QString getStudentPath() const;
	std::vector<QString> getAllClassName() const;
	bool addClassName(const QString& name);
	std::vector<QString> getAllStudentName() const;
	bool addStudentName(const QString& name);
};
#define DATA_CENTER_INSTANCE DataCenter::getInstance()
