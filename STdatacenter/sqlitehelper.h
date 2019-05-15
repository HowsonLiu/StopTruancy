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
	static int CountCallBack(void*, int, char**, char**);	// 回调函数必须是静态

public:
	SQLiteHelper(const QString&);		// 打开db文件
	~SQLiteHelper();
	inline bool isValid() const { return m_bValid; }
	bool Init();						// 创建表
	bool AddStudent(const QString&);	// sqlite 不支持添加多项
	bool AddRecord(const QString&, const std::vector<QString>&);
	bool GetRecordNums(int*) const;
	bool GetStudentAttendanceNums(const QString&, int*);
};

// 列名不能以数字开头
QString StuName2Col(const QString&);
QString Col2StuName(const QString&);