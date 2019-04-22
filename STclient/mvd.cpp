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
