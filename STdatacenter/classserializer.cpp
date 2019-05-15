#include "classserializer.h"
#include "datacenter.h"
#include "sqlitehelper.h"
#include "studentserializer.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <opencv2/face.hpp>

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

int ClassSerializer::init()
{
	QDir dir;
	if (!dir.exists(m_path) && (!dir.mkpath(m_path) || !dir.mkpath(m_lessonPath))) return CS_API_ERROR;
	SQLiteHelper helper(m_dbPath);
	if (!helper.isValid()) return CS_SQL_ERROR;
	if (!helper.Init()) return CS_SQL_ERROR;
	if (DATA_CENTER_INSTANCE->addClassName(m_name)) return CS_API_ERROR;
	return CS_OK;
}

bool ClassSerializer::exists() const
{
	return QDir(m_path).exists();
}

bool ClassSerializer::deletes()
{
	for (QString studentName : students()) {
		StudentSerializer student(studentName);
		if (student.exists()) student.delClass(m_name);
	}
	DATA_CENTER_INSTANCE->delClassName(m_name);
	QDir dir(m_path);
	return dir.removeRecursively();
}

int ClassSerializer::addStudent(const QString& name)
{
	QFile file(m_cfgPath);
	StudentSerializer student(name);
	if (!student.exists()) return CS_STUDENT_NOT_EXIST;
	SQLiteHelper helper(m_dbPath);
	if (!helper.isValid()) return CS_SQL_ERROR;
	if (!helper.AddStudent(name)) return CS_SQL_ERROR;
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return CS_API_ERROR;
	QTextStream stream(&file);
	while (!stream.atEnd()) {
		QString curStudent = stream.readLine();
		if (QString::compare(name, curStudent) == 0) return CS_ALREADY_DONE;	// 去重
	}
	stream << name << endl;
	student.addClass(m_name);
	file.close();
	return CS_OK;
}

std::vector<QString> ClassSerializer::students() const
{
	std::vector<QString> res;
	QFile studentFile(m_cfgPath);
	if (studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&studentFile);
		while (!stream.atEnd()) {
			res.push_back(stream.readLine());
		}
	}
	studentFile.close();
	return res;
}

void ClassSerializer::getStudents(QList<QString>* ll)
{
	QFile studentFile(m_cfgPath);
	if (studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&studentFile);
		while (!stream.atEnd()) {
			ll->push_back(stream.readLine());
		}
	}
	studentFile.close();
}

void ClassSerializer::getLessonImages(QList<Lesson>* pLessons)
{
	QDir dir(m_lessonPath);
	if (!pLessons || !dir.exists()) return;
	QStringList filters;
	filters << "*.png" << "*.jpg" << "*.pgm";
	dir.setNameFilters(filters);
	QStringList imageNameList = dir.entryList();
	for (QString imageName : imageNameList) {
		Lesson l;
		if (!l.photo.load(dir.filePath(imageName))) continue;
		l.name = imageName;
		pLessons->push_back(l);
	}
}

int ClassSerializer::addLesson(const cv::Mat& mat, const QString& name, const std::vector<QString>& attendStus)
{
	if (mat.empty()) return CS_INVALID_PARAM;
	QString path = m_lessonPath + QString("\\%1.jpg").arg(name);
	if (QFile(path).exists()) return CS_INVALID_PARAM;
	SQLiteHelper helper(m_dbPath);
	if (!helper.isValid() || !helper.AddRecord(name, attendStus)) return CS_SQL_ERROR;
	if (!cv::imwrite(path.toStdString(), mat)) return CS_API_ERROR;
	return CS_OK;
}

int ClassSerializer::getLessonNum(int* num)
{
	SQLiteHelper helper(m_dbPath);
	if (!helper.isValid() || !helper.GetRecordNums(num)) return CS_SQL_ERROR;
	return CS_OK;
}

int ClassSerializer::getStudentAttendances(const QString& name, int* num)
{
	SQLiteHelper helper(m_dbPath);
	if (!helper.isValid() || !helper.GetStudentAttendanceNums(name, num)) return CS_SQL_ERROR;
	return CS_OK;
}

int ClassSerializer::trains()
{
	std::vector<cv::Mat> mats;
	std::vector<int> names;
	for (QString name : students()) {
		StudentSerializer student(name);
		if (!student.exists()) continue;	// 这种情况不应该存在
		student.readTrainImages(&mats);
		while (mats.size() > names.size())
			names.push_back(name.toInt());
	}
	if (mats.size() <= 0) return CS_STUDENT_NOT_EXIST;
	try {
		cv::Ptr<cv::face::EigenFaceRecognizer> model = cv::face::EigenFaceRecognizer::create();
		model->train(mats, names);
		model->write(m_xmlPath.toStdString());
	}
	catch (std::exception& e) {
		return CS_API_ERROR;
	}
	return CS_OK;
}
