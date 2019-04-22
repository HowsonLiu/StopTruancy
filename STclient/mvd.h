#pragma once
#include <QAbstractItemModel>
#include <vector>

class AllStudentsModel : public QAbstractItemModel
{
	Q_OBJECT
private:
	std::vector<QString> m_students;

public:
	explicit AllStudentsModel(QObject* parent = nullptr);
	~AllStudentsModel();
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent /* = QModelIndex() */) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent /* = QModelIndex() */) const override;
};

