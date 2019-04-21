#pragma once
#include <QString>
#include <vector>

class sqlite3;
class SQLiteHelper
{
private:
	sqlite3* m_db;
	bool m_bValid;

private:
	static int CountCallBack(void*, int, char**, char**);	// �ص����������Ǿ�̬

public:
	SQLiteHelper(const QString&);
	~SQLiteHelper();
	inline bool isValid() const { return m_bValid; }
	bool Init();
	bool AddCol(const QString&);	// sqlite ��֧����Ӷ���
	bool AddRecord(const QString&, const std::vector<QString>&);
	bool GetRecordNums(int*) const;
	bool GetStudentAttendanceNums(const QString&, int*);
};

// �������������ֿ�ͷ
QString StuName2Col(const QString&);
QString Col2StuName(const QString&);