#pragma once
#include <QWidget>

class Student;
class QLabel;
class QPushButton;
class QTreeView;
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
	QTreeView* m_attendancesList;
	AttendancesModel* m_attendancesModel;

public:
	StudentWidget(QWidget *parent = Q_NULLPTR);
	~StudentWidget();
	void SetStudent(Student*);
	QString GetCurName() const;

public slots:
	void onOptimizeButtonClick();
};

