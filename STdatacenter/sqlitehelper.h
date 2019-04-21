#pragma once
#include <QString>
#include <vector>

class sqlite3;
class SQLiteHelper
{
private:
	sqlite3* m_db;
	bool m_bValid;

public:
	SQLiteHelper(const QString&);
	~SQLiteHelper();
	inline bool isValid() const { return m_bValid; }
	bool Init();
	bool AddCol(const QString&);	// sqlite ��֧����Ӷ���
};

// �������������ֿ�ͷ
QString StuName2Col(const QString&);
QString Col2StuName(const QString&);