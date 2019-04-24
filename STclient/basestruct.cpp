#include "basestruct.h"
#include "../STdatacenter/studentserializer.h"
#include "../STdatacenter/classserializer.h"
#include <QPixmap>

Student::Student(const QString& name)
	: m_name(name)
{
	m_serializer = new StudentSerializer(name);
	m_serializer->ReadProfilePhoto(&m_photo);
	for (QString className : m_serializer->Classes()) {
		ClassSerializer cls(className);
		if (cls.Exist()) {
			Attendance attend;
			attend.className = className;
			attend.studentName = m_name;
			cls.GetLessonNum(&attend.allNum);
			cls.GetStudentAttendances(m_name, &attend.attendanceNum);
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
	return m_serializer && m_serializer->Exist();
}

Class::Class(const QString& name)
	: m_name(name)
{
	m_serializer = new ClassSerializer(name);
	std::vector<QPixmap> photos;
	std::vector<QString> names;
	m_serializer->GetLessonsImage(&photos, &names);
	for (QString stuName : m_serializer->Students()) {
		StudentSerializer stu(stuName);
		if (stu.Exist()) {
			Attendance attend;
			attend.className = m_name;
			attend.studentName = stuName;
			m_serializer->GetLessonNum(&attend.allNum);
			m_serializer->GetStudentAttendances(stuName, &attend.attendanceNum);
			m_attendances.push_back(attend);
		}
	}
}

Class::~Class()
{
}
