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

class ClassSerializer;
class Class
{
private:
	QString m_name;
	std::vector<QPixmap> m_photos;
	std::vector<QString> m_photosName;
	std::vector<Attendance> m_attendances;

	ClassSerializer* m_serializer;

public:
	Class(const QString&);
	~Class();
	inline QString getName() const { return m_name; }
	inline std::vector<Attendance> getAttendances() const { return m_attendances; }
};
