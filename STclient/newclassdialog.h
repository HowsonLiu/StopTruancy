#pragma once
#include <QDialog>
#include <vector>

class QLineEdit;
class QListView;
class QLabel;
class QPushButton;
class AllStudentsModel;
class NewClassDialog : public QDialog
{
	Q_OBJECT
private:
	QLineEdit* m_nameEdit;
	QLabel* m_tipLabel;
	QLineEdit* m_searchEdit;
	QListView* m_listView;
	QLabel* m_numLabel;
	QPushButton* m_okButton;
	AllStudentsModel* m_allStudentsModel;

	QString* m_name;
	std::vector<QString>* m_studentNames;
	bool bVaildName;
	bool bVaildStudents;

public:
	NewClassDialog(QString*, std::vector<QString>*, QWidget* parent = nullptr);
	~NewClassDialog();

public slots:
	void onTextChanged(const QString&);
	void onItemClicked();
};

