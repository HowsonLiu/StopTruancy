#pragma once
#include <QWidget>

class Student;
class QLabel;
class QPushButton;
class QListView;
class AttendancesModel;
class StudentWidget : public QWidget
{
	Q_OBJECT
private:
	Student* m_student;
	QPixmap m_defaultPhoto;
	QString m_defaultName;

	QLabel* m_photoLabel;
	QLabel* m_nameLabel;
	QLabel* m_optimizeLabel;
	QPushButton* m_optimizeButton;
	QListView* m_attendancesList;
	AttendancesModel* m_attendancesModel;

public:
	StudentWidget(QWidget *parent = Q_NULLPTR);
	~StudentWidget();
	void SetStudent(Student*);
	QString GetCurName() const;

signals:
	void sigSelectClass(const QString&);

public slots:
	void onOptimizeButtonClick();
	void onItemDoubleClick(const QModelIndex&);
};

