#include "basestruct.h"
#include "../STdatacenter/studentserializer.h"
#include "../STdatacenter/classserializer.h"
#include <QImage>

Student::Student(const QString& name)
	: m_name(name)
{
	m_serializer = new StudentSerializer(name);
	cv::Mat mat;
	m_serializer->ReadProfilePhoto(&mat);
	if (!mat.empty()) 
		m_photo = new QImage((const uchar *)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
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
	if (m_photo) delete m_photo;
}

inline bool Student::Exist() const
{
	return m_serializer && m_serializer->Exist();
}

Class::Class()
{
}

Class::~Class()
{
}
