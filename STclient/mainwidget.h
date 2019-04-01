#pragma once

#include <QWidget>

class LeftWidget;
class StudentWidget;
class ClassWidget;
class MainWidget : public QWidget
{
	Q_OBJECT
public:
	MainWidget(QWidget *parent = Q_NULLPTR);
	~MainWidget();

private:
	LeftWidget* m_leftWidget;
	StudentWidget* m_studentWidget;
	ClassWidget* m_classWidget;
};
