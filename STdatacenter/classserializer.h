#pragma once
#include <QString>
#include <vector>
#include <opencv2/opencv.hpp>
#include <QPixmap>

#define CS_ALREADY_DONE 1
#define CS_OK 0
#define CS_STUDENT_NOT_EXIST -1
#define CS_API_ERROR -2
#define CS_SQL_ERROR -3
#define CS_INVALID_PARAM -4
#define CS_SAME_NAME -5

struct Lesson
{
	QPixmap photo;
	QString name;
};

class ClassSerializer
{
private:
	const QString m_name;
	const QString m_path;
	const QString m_lessonPath;
	const QString m_xmlPath;
	const QString m_cfgPath;
	const QString m_dbPath;

public:
	ClassSerializer(const QString&);
	~ClassSerializer();
	inline QString getXmlPath() const { return m_xmlPath; }
	int Init();
	bool Exist() const;
	bool Delete();
	int AddStudent(const QString&);
	int AddStudents(const std::vector<QString>&);
	std::vector<QString> Students() const;
	void GetStudents(QList<QString>*);
	void GetLessonsImage(QList<Lesson>*);
	int AddLesson(const cv::Mat&, const QString&, const std::vector<QString>&);
	int GetLessonNum(int*);
	int GetStudentAttendances(const QString&, int*);
	int Train();
};

