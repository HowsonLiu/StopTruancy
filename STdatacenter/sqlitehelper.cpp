#include "sqlitehelper.h"
#include <sqlite3.h>

/**
 *@param:data 
 *@param:argc number of columns
 *@param:argv data of columns
 *@param:azColName name of columns
 *@return:sqlite3_exec function result
 */
int SQLiteHelper::CountCallBack(void* data, int argc, char** argv, char** azColName)
{
	if (argc <= 0) return SQLITE_ERROR;
	*static_cast<int*>(data) = QString(argv[0]).toInt();
	return SQLITE_OK;
}

SQLiteHelper::SQLiteHelper(const QString& path)
	: m_bValid(true)
{
	if (sqlite3_open(path.toUtf8(), &m_db) != SQLITE_OK) m_bValid = false;
}


SQLiteHelper::~SQLiteHelper()
{
	sqlite3_close(m_db);
}

bool SQLiteHelper::Init()
{
	QString sql = "CREATE TABLE LESSON(NAME CHAR(50) PRIMARY KEY NOT NULL);";
	return sqlite3_exec(m_db, sql.toUtf8(), nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool SQLiteHelper::AddStudent(const QString& col)
{
	QString sql = "ALTER TABLE LESSON ADD COLUMN %1 INT DEFAULT 0;";	// sqlite√ª”–bool
	sql = sql.arg(StuName2Col(col));
	return sqlite3_exec(m_db, sql.toUtf8(), nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool SQLiteHelper::AddRecord(const QString& lesson, const std::vector<QString>& students)
{
	QString sql;
	if (!students.size()) {
		sql = QString("INSERT INTO LESSON(NAME) VALUES ('%1');").arg(lesson);
	}
	else {
		sql = "INSERT INTO LESSON(NAME, %1) VALUES ('%2', %3);";
		QString cols, values;
		for (int i = 0; i < students.size() - 1; ++i) {
			cols += StuName2Col(students[i]) + ", ";
			values += "1, ";
		}
		cols += StuName2Col(students[students.size() - 1]);
		values += "1";
		sql = sql.arg(cols, lesson, values);
	}
	return sqlite3_exec(m_db, sql.toUtf8(), nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool SQLiteHelper::GetRecordNums(int* num) const
{
	QString sql = "SELECT COUNT(*) FROM LESSON";
	return sqlite3_exec(m_db, sql.toUtf8(), &CountCallBack, static_cast<void*>(num), nullptr) == SQLITE_OK;
}

bool SQLiteHelper::GetStudentAttendanceNums(const QString& name, int* num)
{
	QString sql = QString("SELECT COUNT(*) FROM LESSON WHERE %1 <> 0").arg(StuName2Col(name));
	return sqlite3_exec(m_db, sql.toUtf8(), &CountCallBack, static_cast<void*>(num), nullptr) == SQLITE_OK;
}

QString StuName2Col(const QString& name) {
	return QString("_%1").arg(name);
}

QString Col2StuName(const QString& col) {
	return col.right(col.size() - 1);
}