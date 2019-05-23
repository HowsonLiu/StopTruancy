#pragma once
#include <QString>
#include <vector>

#define ROOT_PATH "D:\\tmp\\data"

class DataCenter
{
private:
	const QString m_rootPath;				// 数据中心的根路径
	const QString m_classesCacheStcPath;	// 班级缓存，里面存有所有班级的名字，避免每次查询遍历文件夹
	const QString m_studentsCacheStsPath;	// 学生缓存
	const QString m_classesFolderPath;		// 存放班级的父文件夹
	const QString m_studentsFolderPath;		// 存放学生的父文件夹
	const QString m_faceDetectionXmlPath;	// 人脸检测的xml文件

private:
	DataCenter();
	~DataCenter();

public:
	static DataCenter* getInstance();
	QString getRootPath() const;
	QString getClassPath() const;
	QString getStudentPath() const;
	QString getFaceDetectionXmlPath() const;
	std::vector<QString> getAllClassName() const;
	bool addClassName(const QString& name);
	bool delClassName(const QString& name);
	std::vector<QString> getAllStudentName() const;
	bool addStudentName(const QString& name);
	bool delStudentName(const QString& name);
};
#define DATA_CENTER_INSTANCE DataCenter::getInstance()
