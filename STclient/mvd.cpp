#include "mvd.h"
#include "../STdatacenter/datacenter.h"
#include <vector>

AllStudentsModel::AllStudentsModel(QObject* parent)
	: QAbstractItemModel(parent)
{
	for (QString name : DATA_CENTER_INSTANCE->getAllStudentName()) {
		m_students.push_back(name);
	}
}


AllStudentsModel::~AllStudentsModel()
{
}

int AllStudentsModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return m_students.size();	// 行数
}

int AllStudentsModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return 1;	// 列数
}

QVariant AllStudentsModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	int row = index.row();
	int column = index.column();	// 要获取数据的行列
	QString name = m_students.at(row);
	switch (role)
	{
	case Qt::DisplayRole:
		return name;	// 简单的只返回名字就可以了
	default:
		break;
	}
	return QVariant();
}

bool AllStudentsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::DisplayRole) {
		int row = index.row();
		m_students.replace(row, value.toString());	// 这里对刚才瞎jb填的值进行更正
		emit(dataChanged(index, index));
		return true;
	}
	return false;
}

QModelIndex AllStudentsModel::parent(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return QModelIndex();	// 都没有父节点
}

QModelIndex AllStudentsModel::index(int row, int column, const QModelIndex & parent) const
{
	if(row < 0 || column < 0 || column >= columnCount(parent))
		return QModelIndex();
	return createIndex(row, column);
}

bool AllStudentsModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row + count - 1);
	m_students.insert(row, QString());	// 这里是瞎jb插入一个空值
	endInsertRows();
	return true;
}

bool AllStudentsModel::removeRows(int row, int count, const QModelIndex& parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for (int i = 0; i < count; ++i)
		m_students.removeAt(row);	// 不用++
	endRemoveRows();
	return true;
}

AllClassesModel::AllClassesModel(QObject* parent)
	: QAbstractItemModel(parent)
	, m_classes(DATA_CENTER_INSTANCE->getAllClassName())
{
}

AllClassesModel::~AllClassesModel()
{
}

int AllClassesModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return m_classes.size();
}

int AllClassesModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant AllClassesModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	int row = index.row();
	int column = index.column();
	QString name = m_classes.at(row);
	switch (role)
	{
	case Qt::DisplayRole:
		return name;	
	default:
		break;
	}
	return QVariant();
}

QModelIndex AllClassesModel::parent(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}

QModelIndex AllClassesModel::index(int row, int column, const QModelIndex & parent) const
{
	if (row < 0 || column < 0 || column >= columnCount(parent))
		return QModelIndex();
	return createIndex(row, column);
}

AttendancesModel::AttendancesModel(QObject * parent)
	: QAbstractItemModel(parent)
{
}

AttendancesModel::~AttendancesModel()
{
}

void AttendancesModel::SetAttendances(const std::vector<Attendance>& attendances)
{
	beginResetModel();	// 重置时需要做的
	m_attendances.clear();
	for (Attendance att : attendances) {
		m_attendances.push_back(att);
	}
	endResetModel();
}

int AttendancesModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return m_attendances.size();
}

int AttendancesModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 3;	// 三列，分别是学生名，课堂名，考勤字符串
}

QVariant AttendancesModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	int row = index.row();
	int column = index.column();
	Attendance att = m_attendances.at(row);
	switch (role)
	{
	case Qt::DisplayRole:
		if (column == STUDENT_NAME_INDEX)
			return att.studentName;
		else if (column == CLASS_NAME_INDEX)
			return att.className;
		else if (column == ATTENDANCE_INDEX)
			return QString("%1/%2").arg(att.attendanceNum).arg(att.allNum);
	default:
		break;
	}
	return QVariant();
}

QModelIndex AttendancesModel::parent(const QModelIndex & index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}

QModelIndex AttendancesModel::index(int row, int column, const QModelIndex& parent) const
{
	if (row < 0 || column < 0 || column >= columnCount(parent))
		return QModelIndex();
	return createIndex(row, column);
}
