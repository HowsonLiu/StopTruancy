#pragma once
#include <QString>
#include <QList>
#include <QPixmap>
#include "../STdatacenter/classserializer.h"

class QPixmap;
struct Attendance
{
	QString studentName;
	QString className;
	int attendanceNum;
	int allNum;
};

class StudentSerializer;
class Student
{
private:
	QString m_name;
	QPixmap m_photo;
	QList<Attendance> m_attendances;

	StudentSerializer* m_serializer;

public:
	Student(const QString&);
	~Student();
	inline bool Exist() const;
	inline QString getName() const { return m_name; }
	inline QPixmap getPhoto() const { return m_photo; }
	inline QList<Attendance> getAttendances() const { return m_attendances; }
};

class ClassSerializer;
class Class
{
private:
	QString m_name;
	QList<Lesson> m_lessons;
	QList<Attendance> m_attendances;

	ClassSerializer* m_serializer;

public:
	Class(const QString&);
	~Class();
	inline QString getName() const { return m_name; }
	inline QList<Attendance> getAttendances() const { return m_attendances; }
	inline QList<Lesson> getLessons() const { return m_lessons; }
};
