#pragma once
#include <QWidget>

class QListView;
class QTreeView;
class Class;
class QLabel;
class QPushButton;
class AttendancesModel;
class LessonsModel;
class ClassWidget : public QWidget
{
	Q_OBJECT
private:
	Class* m_class;
	QString m_defaultName;

	QLabel* m_nameLabel;
	QPushButton* m_trainButton;
	QLabel* m_trainLabel;
	QLabel* m_addLessonLabel;
	QPushButton* m_addLessonButton;
	QListView* m_lessonList;
	QTreeView* m_attendanceList;
	AttendancesModel* m_attendanceModel;
	LessonsModel* m_lessonsModel;

public:
	ClassWidget(QWidget *parent = Q_NULLPTR);
	~ClassWidget();
	void SetClass(Class* cls);
	QString GetCurName() const;

signals:
	void sigSelectStudent(const QString&);

public slots:
	void onLessonItemDoubleClick(const QModelIndex&);
	void onAttendanceItemDoubleClick(const QModelIndex&);
	void onTrainButtonClick();
	void onAddLessonButtonClick();
};

