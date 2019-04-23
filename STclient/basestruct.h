#pragma once
#include <QString>
#include <vector>

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
	QPixmap* m_photo;
	std::vector<Attendance> m_attendances;

	StudentSerializer* m_serializer;

public:
	Student(const QString&);
	~Student();
	inline bool Exist() const;
	inline QString getName() const { return m_name; }
	inline QPixmap* getPhoto() const { return m_photo; }
	inline std::vector<Attendance> getAttendances() const { return m_attendances; }
};

class Class
{
private:
	QString name;
	std::vector<QPixmap*> photos;
	std::vector<Attendance> attendances;

public:
	Class(const QString&);
	~Class();
	inline QString getName() const { return name; }
};
