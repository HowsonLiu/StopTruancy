#pragma once
#include <QString>
#include <vector>

#define ROOT_PATH ".\\data"

class DataCenter
{
private:
	const QString m_rootPath;				// �������ĵĸ�·��
	const QString m_classesCacheStcPath;	// �༶���棬����������а༶�����֣�����ÿ�β�ѯ�����ļ���
	const QString m_studentsCacheStsPath;	// ѧ������
	const QString m_classesFolderPath;		// ��Ű༶�ĸ��ļ���
	const QString m_studentsFolderPath;		// ���ѧ���ĸ��ļ���
	const QString m_faceDetectionXmlPath;	// ��������xml�ļ�

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
