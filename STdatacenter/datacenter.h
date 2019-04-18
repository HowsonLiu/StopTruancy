#pragma once
#include <QString>
#include <vector>

#define ROOT_PATH "D:\\tmp\\data"

class DataCenter
{
private:
	const QString m_rootPath;
	const QString m_allClassPath;
	const QString m_allStudentPath;

private:
	DataCenter();
	~DataCenter();

public:
	static DataCenter* getInstance();
	std::vector<QString> getAllClassName() const;
	bool addClassName(const QString& name);
	std::vector<QString> getAllStudentName() const;
	bool addStudentName(const QString& name);
};
#define DATA_CENTER_INSTANCE DataCenter::getInstance()
