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
	QString name;
	QPixmap photo;
	std::vector<Attendance> attendances;

public:
	Student();
	~Student();
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
};
