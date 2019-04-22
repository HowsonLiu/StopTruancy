#pragma once
#include <QWidget>

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

public slots:
	void onAddButtonClick();
	void onSwitchComboBox(int);
};

class EmptyWidget : public QWidget 
{
	Q_OBJECT
public:
	EmptyWidget(QWidget* parent = Q_NULLPTR);
	~EmptyWidget();
};