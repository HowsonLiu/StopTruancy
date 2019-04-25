#pragma once
#include <QDialog>

class QLineEdit;
class QListView;
class QLabel;
class NewClassDialog : public QDialog
{
	Q_OBJECT
private:
	QLineEdit* m_nameEdit;
	QLabel* m_tipLabel;
	QLineEdit* m_searchEdit;
	QListView* m_listView;

public:
	NewClassDialog(QWidget* parent = nullptr);
	~NewClassDialog();
};

