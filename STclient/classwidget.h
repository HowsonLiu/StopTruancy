#pragma once
#include <QWidget>

class QListView;
class Class;
class QLabel;
class QPushButton;
class ClassWidget : public QWidget
{
	Q_OBJECT
private:
	Class* m_class;
	QString m_defaultName;

	QLabel* m_nameLabel;
	QPushButton* m_addLessonButton;
	QListView* m_lessonList;
	QListView* m_attendanceList;

public:
	ClassWidget(QWidget *parent = Q_NULLPTR);
	~ClassWidget();
	void SetClass(Class* cls);
};

