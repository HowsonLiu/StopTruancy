#include "mvd.h"
#include "../STdatacenter/datacenter.h"


AllStudentsModel::AllStudentsModel(QObject* parent)
	: QAbstractItemModel(parent)
	, m_students(DATA_CENTER_INSTANCE->getAllStudentName())
{
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
