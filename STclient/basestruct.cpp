#include "basestruct.h"
#include "../STdatacenter/studentserializer.h"
#include "../STdatacenter/classserializer.h"
#include <QPixmap>

Student::Student(const QString& name)
	: m_name(name)
{
	m_serializer = new StudentSerializer(name);
	m_serializer->readProfilePhoto(&m_photo);
	for (QString className : m_serializer->classes()) {
		ClassSerializer cls(className);
		if (cls.exists()) {
			Attendance attend;
			attend.className = className;
			attend.studentName = m_name;
			cls.getLessonNum(&attend.allNum);
			cls.getStudentAttendances(m_name, &attend.attendanceNum);
			m_attendances.push_back(attend);
		}
	}
}


Student::~Student()
{
	if (m_serializer) delete m_serializer;
}

inline bool Student::Exist() const
{
	return m_serializer && m_serializer->exists();
}

Class::Class(const QString& name)
	: m_name(name)
{
	m_serializer = new ClassSerializer(name);
	m_serializer->getLessonImages(&m_lessons);
	for (QString stuName : m_serializer->students()) {
		StudentSerializer stu(stuName);
		if (stu.exists()) {
			Attendance attend;
			attend.className = m_name;
			attend.studentName = stuName;
			m_serializer->getLessonNum(&attend.allNum);
			m_serializer->getStudentAttendances(stuName, &attend.attendanceNum);
			m_attendances.push_back(attend);
		}
	}
}

Class::~Class()
{
}
