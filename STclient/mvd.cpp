#include "mvd.h"
#include "Resources.h"
#include "../STdatacenter/datacenter.h"
#include <vector>
#include <QIcon>
#include <QPainter>
#include <QStyleOptionViewItem>

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

bool AllClassesModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (index.isValid() && role == Qt::DisplayRole) {
		int row = index.row();
		m_classes.replace(row, value.toString());	// ����Ըղ�Ϲjb���ֵ���и���
		emit(dataChanged(index, index));
		return true;
	}
	return false;
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

bool AllClassesModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(parent, row, row + count - 1);
	m_classes.insert(row, QString());	// ������Ϲjb����һ����ֵ
	endInsertRows();
	return true;
}

bool AllClassesModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for (int i = 0; i < count; ++i)
		m_classes.removeAt(row);	// ����++
	endRemoveRows();
	return true;
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
	return 1;
}

QVariant AttendancesModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	int row = index.row();
	int column = index.column();
	Attendance att = m_attendances.at(row);
	switch (role)
	{
	case Qt::UserRole + STUDENT_NAME_INDEX:
		return att.studentName;
	case Qt::UserRole + CLASS_NAME_INDEX:
		return att.className;
	case Qt::UserRole + ATTENDANCE_INDEX:
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
	case Qt::UserRole:		// ��������ͼ
		return ls.photo;	
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

DefaultStuAndClsDelegate::DefaultStuAndClsDelegate(QObject* parent /* = nullptr */)
	: QStyledItemDelegate(parent)
{

}

DefaultStuAndClsDelegate::~DefaultStuAndClsDelegate()
{
}

void DefaultStuAndClsDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.isValid()) {
		painter->save();
		QString name = index.data(Qt::DisplayRole).toString();

		// selected
		if (option.state.testFlag(QStyle::State_Selected)) {
			painter->fillRect(option.rect, g_leftBackgroundSelectedColor);
			QRectF redRect(option.rect.left(), option.rect.top(), 3, option.rect.height());
			painter->fillRect(redRect, g_neteaseMusicTitleRed);
		}

		QRectF textRect(option.rect.left() + 3, option.rect.top(), option.rect.width(), option.rect.height());
		// selected or hover
		if (option.state.testFlag(QStyle::State_Selected) || option.state.testFlag(QStyle::State_MouseOver))
			painter->setPen(QPen(g_leftTextSelectedColor));
		else
			painter->setPen(QPen(g_leftTextUnselectedColor));
		painter->setFont(QFont(g_defaultFont, 20));
		painter->drawText(textRect, name);
		painter->restore();
	}
}

QSize DefaultStuAndClsDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex & index) const
{
	Q_UNUSED(index);
	return QSize(option.rect.width(), 40);
}

StudentsModel::StudentsModel(QObject * parent)
	: QAbstractItemModel(parent)
{
}

StudentsModel::~StudentsModel()
{
}

void StudentsModel::SetStudents(const QList<QString>& students)
{
	m_students = students;
}

int StudentsModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return m_students.size();
}

int StudentsModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant StudentsModel::data(const QModelIndex & index, int role) const
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

QModelIndex StudentsModel::parent(const QModelIndex & index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}

QModelIndex StudentsModel::index(int row, int column, const QModelIndex & parent) const
{
	if (row < 0 || column < 0 || column >= columnCount(parent))
		return QModelIndex();
	return createIndex(row, column);
}

StudentAttendanceDelegate::StudentAttendanceDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{
}

StudentAttendanceDelegate::~StudentAttendanceDelegate()
{
}

void StudentAttendanceDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (index.isValid()) {
		painter->save();
		QString stuName = index.data(Qt::UserRole + STUDENT_NAME_INDEX).toString();
		QString attendance = index.data(Qt::UserRole + ATTENDANCE_INDEX).toString();

		// single index
		if (index.row() % 2) {
			painter->fillRect(option.rect, g_attendanceSingleIndexBackgroundColor);
		}

		// hover
		if (option.state.testFlag(QStyle::State_MouseOver)) {
			painter->fillRect(option.rect, g_attendanceHoverColor);
		}

		// selected
		if (option.state.testFlag(QStyle::State_Selected)) {
			painter->fillRect(option.rect, g_attendanceSelectedColor);
		}

		QRectF nameRect(option.rect.left() + 5, option.rect.top(), option.rect.width() / 2 - 5, option.rect.height());
		QRectF attendRect(option.rect.left() + option.rect.width() / 2, option.rect.top(), option.rect.width() / 2, option.rect.height());
		painter->setPen(QPen(Qt::black));
		painter->setFont(QFont(g_defaultFont, 20));
		painter->drawText(nameRect, stuName);
		painter->drawText(attendRect, Qt::AlignRight, attendance);

		painter->restore();
	}
}

QSize StudentAttendanceDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	Q_UNUSED(index);
	return QSize(option.rect.width(), 40);
}

ClassAttendanceDelegate::ClassAttendanceDelegate(QObject* parent /* = nullptr */)
	:QStyledItemDelegate(parent)
{
}

ClassAttendanceDelegate::~ClassAttendanceDelegate()
{
}

void ClassAttendanceDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (index.isValid()) {
		painter->save();
		QString clsName = index.data(Qt::UserRole + CLASS_NAME_INDEX).toString();
		QString attendance = index.data(Qt::UserRole + ATTENDANCE_INDEX).toString();

		// single index
		if (index.row() % 2) {
			painter->fillRect(option.rect, g_attendanceSingleIndexBackgroundColor);
		}

		// hover
		if (option.state.testFlag(QStyle::State_MouseOver)) {
			painter->fillRect(option.rect, g_attendanceHoverColor);
		}

		// selected
		if (option.state.testFlag(QStyle::State_Selected)) {
			painter->fillRect(option.rect, g_attendanceSelectedColor);
		}

		QRectF nameRect(option.rect.left() + 5, option.rect.top(), option.rect.width() / 2 - 5, option.rect.height());
		QRectF attendRect(option.rect.left() + option.rect.width() / 2, option.rect.top(), option.rect.width() / 2, option.rect.height());
		painter->setPen(QPen(Qt::black));
		painter->setFont(QFont(g_defaultFont, 20));
		painter->drawText(nameRect, clsName);
		painter->drawText(attendRect, Qt::AlignRight, attendance);

		painter->restore();
	}
}

QSize ClassAttendanceDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	Q_UNUSED(index);
	return QSize(option.rect.width(), 40);
}
