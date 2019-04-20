#pragma once
#include <QString>
#include <vector>

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
	bool Init();
	bool Exist() const;
	bool Delete();
	bool AddStudent(const QString&);
	bool AddStudents(const std::vector<QString>&);
};

