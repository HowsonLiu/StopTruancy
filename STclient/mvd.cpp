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
