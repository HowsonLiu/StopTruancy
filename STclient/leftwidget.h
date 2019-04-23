#pragma once
#include <QWidget>
#include "facecollectionwidget.h"

class QLabel;
class QComboBox;
class QLineEdit;
class QListView;
class QPushButton;
class AllStudentsModel;
class AllClassesModel;
class LeftWidget : public QWidget
{
	Q_OBJECT
public:
	LeftWidget(QWidget *parent = Q_NULLPTR);
	~LeftWidget();

private:
	QLabel* m_signLabel;
	QComboBox* m_comboBox;
	QLineEdit* m_searchEdit;
	QListView* m_listView;
	QPushButton* m_addButton;
	QPushButton* m_delButton;

	AllStudentsModel* m_allStudentsModel;
	AllClassesModel* m_allClassesModel;

signals:
	void sigSelectStudent(const QString&);
	void sigSelectClass(const QString&);
	void sigDelStudent(const QString&);
	void sigDelClass(const QString&);

public slots:
	void onAddButtonClick();
	void onDelButtonClick();
	void onSwitchComboBox(int);
	void onItemDoubleClick(const QModelIndex&);

public:
	void AddStudent(const QString& name, const std::vector<cv::Mat>&);
	void DelStudent();
};

class EmptyWidget : public QWidget 
{
	Q_OBJECT
public:
	EmptyWidget(QWidget* parent = Q_NULLPTR);
	~EmptyWidget();
};