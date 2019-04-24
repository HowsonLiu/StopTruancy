#pragma once
#include <QAbstractItemModel>
#include "basestruct.h"
#include <QList>
#include <QStyledItemDelegate>

class AllStudentsModel : public QAbstractItemModel
{
	Q_OBJECT
private:
	QList<QString> m_students;	// QList¸ü¼æÈÝModel

public:
	explicit AllStudentsModel(QObject* parent = nullptr);
	~AllStudentsModel();
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */) override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual bool insertRows(int row, int count, const QModelIndex &parent /* = QModelIndex() */) override;
	virtual bool removeRows(int row, int count, const QModelIndex &parent /* = QModelIndex() */) override;
};

class AllClassesModel : public QAbstractItemModel 
{
	Q_OBJECT
private:
	QList<QString> m_classes;

public:
	explicit AllClassesModel(QObject* parent = nullptr);
	~AllClassesModel();
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex() */) const override;
};

#define STUDENT_NAME_INDEX 0
#define CLASS_NAME_INDEX 1
#define ATTENDANCE_INDEX 2

class AttendancesModel : public QAbstractItemModel
{
	Q_OBJECT
private:
	QList<Attendance> m_attendances;

public:
	explicit AttendancesModel(QObject* parent = nullptr);
	~AttendancesModel();
	void SetAttendances(const QList<Attendance>&);
	virtual int rowCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual QVariant data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex() */) const override;
};

class LessonsModel : public QAbstractItemModel
{
	Q_OBJECT
private:
	QList<Lesson> m_lessons;

public:
	explicit LessonsModel(QObject* parent = nullptr);
	~LessonsModel();
	void SetLessons(const QList<Lesson>&);
	virtual int rowCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual QVariant data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex() */) const override;
};

class DefaultStuAndClsDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit DefaultStuAndClsDelegate(QObject* parent = nullptr);
	~DefaultStuAndClsDelegate();
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};