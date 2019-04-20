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
		pvm->push_back(cv::imread(imagePath, 0));	// �����ɫͼ��
	}
}

std::vector<QString> StudentSerializer::Classes()
{
	std::vector<QString> res;
	QFile classesFile(m_cfgPath);
	if (classesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&classesFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	classesFile.close();
	return res;
}

bool StudentSerializer::AddClass(const QString& name)
{
	QFile classesFile(m_cfgPath);
	if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&classesFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return true;	// ȥ��
	}
	stream << name << endl;
	classesFile.close();
	return true;
}

bool StudentSerializer::DelClass(const QString& name)
{
	std::vector<QString> Classes;
	QFile classesFile(m_cfgPath);
	if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Text)) return false;
	QTextStream stream(&classesFile);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) != 0)
			Classes.push_back(curStudent);
	}
	classesFile.resize(0);	// ������д
	for (QString curStudent : Classes) {
		stream << curStudent << endl;
	}
	classesFile.close();
	return true;
}

bool StudentSerializer::Init()
{
	DATA_CENTER_INSTANCE->addStudentName(m_name);
	QDir dir;
	if (!dir.exists(m_path)) return dir.mkpath(m_path);
	return true;
}

bool StudentSerializer::Delete()
{
	QFile file(m_cfgPath);
	if (file.exists() && file.size() > 0) return false;	// ��ѡ�޵Ŀγ�ʱ����ɾ��
	DATA_CENTER_INSTANCE->delStudentName(m_name);
	QDir dir(m_path);
	return dir.removeRecursively();
}

bool StudentSerializer::Exist() const
{
	return QDir(m_path).exists();
}
