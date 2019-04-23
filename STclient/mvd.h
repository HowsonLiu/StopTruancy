#pragma once
#include <QAbstractItemModel>
#include <QList>

class AllStudentsModel : public QAbstractItemModel
{
	Q_OBJECT
private:
	QList<QString> m_students;	// QList������Model

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
};

class AllClassesModel : public QAbstractItemModel 
{
	Q_OBJECT
private:
	std::vector<QString> m_classes;

public:
	explicit AllClassesModel(QObject* parent = nullptr);
	~AllClassesModel();
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex() */) const override;
};