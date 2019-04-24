#include "mvd.h"
#include "../STdatacenter/datacenter.h"
#include <vector>
#include <QIcon>

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
	return m_students.size();	// ����
}

int AllStudentsModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return 1;	// ����
}

QVariant AllStudentsModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	int row = index.row();
	int column = index.column();	// Ҫ��ȡ���ݵ�����
	QString name = m_students.at(row);
	switch (role)
	{
	case Qt::DisplayRole:
		return name;	// �򵥵�ֻ�������־Ϳ�����
	default:
		break;
	}
	return QVariant();
}

bool AllStudentsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::DisplayRole) {
		int row = index.row();
		m_students.replace(row, value.toString());	// ����Ըղ�Ϲjb���ֵ���и���
		emit(dataChanged(index, index));
		return true;
	}
	return false;
}

QModelIndex AllStudentsModel::parent(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return QModelIndex();	// ��û�и��ڵ�
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
	m_students.insert(row, QString());	// ������Ϲjb����һ����ֵ
	endInsertRows();
	return true;
}

bool AllStudentsModel::removeRows(int row, int count, const QModelIndex& parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for (int i = 0; i < count; ++i)
		m_students.removeAt(row);	// ����++
	endRemoveRows();
	return true;
}

AllClassesModel::AllClassesModel(QObject* parent)
	: QAbstractItemModel(parent)
{
	for (QString name : DATA_CENTER_INSTANCE->getAllClassName()) {
		m_classes.push_back(name);
	}
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

void AttendancesModel::SetAttendances(const QList<Attendance>& attendances)
{
	beginResetModel();	// ����ʱ��Ҫ����
	m_attendances = attendances;
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
	return 3;	// ���У��ֱ���ѧ�������������������ַ���
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

LessonsModel::LessonsModel(QObject* parent)
	: QAbstractItemModel(parent)
{
}

LessonsModel::~LessonsModel()
{
}

void LessonsModel::SetLessons(const QList<Lesson>& lesson)
{
	beginResetModel();
	m_lessons = lesson;
	endResetModel();
}

int LessonsModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return m_lessons.size();
}

int LessonsModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant LessonsModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	int row = index.row();
	int column = index.column();
	Lesson ls = m_lessons.at(row);
	switch (role)
	{
	case Qt::DisplayRole:
		return ls.name;
	case Qt::DecorationRole:	// ͼ���ɫ
		return QIcon(ls.photo);
	default:
		break;
	}
	return QVariant();
}

QModelIndex LessonsModel::parent(const QModelIndex & index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}

QModelIndex LessonsModel::index(int row, int column, const QModelIndex & parent) const
{
	if (row < 0 || column < 0 || column >= columnCount(parent))
		return QModelIndex();
	return createIndex(row, column);
}
