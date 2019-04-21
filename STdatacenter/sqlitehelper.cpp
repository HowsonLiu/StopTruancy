#include "sqlitehelper.h"
#include <sqlite3.h>


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

bool SQLiteHelper::AddCol(const QString& col)
{
	QString sql = "ALTER TABLE LESSON ADD COLUMN %1 INT;";	// sqlite√ª”–bool
	sql = sql.arg(StuName2Col(col));
	return sqlite3_exec(m_db, sql.toUtf8(), nullptr, nullptr, nullptr) == SQLITE_OK;
}

QString StuName2Col(const QString& name) {
	return QString("_%1").arg(name);
}

QString Col2StuName(const QString& col) {
	return col.right(col.size() - 1);
}