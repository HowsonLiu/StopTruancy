#pragma once
#include <QString>
#include <QPixmap>
#include <vector>

struct Attendance
{
	QString studentName;
	QString className;
	unsigned int attendanceNum;
	unsigned int allNum;
};

class Student
{
private:
	QString m_name;
	QPixmap m_photo;
	std::vector<Attendance> m_attendances;

	bool m_bValid;

public:
	Student(const QString&);
	~Student();
	inline QString getName() const { return m_name; }
	inline QPixmap getPhoto() const { return m_photo; }
	inline std::vector<Attendance> getAttendances() const { return m_attendances; }
};

class Class
{
private:
	QString name;
	std::vector<QPixmap> photos;
	std::vector<Attendance> attendances;

public:
	Class();
	~Class();
	inline QString getName() const { return name; }
};
