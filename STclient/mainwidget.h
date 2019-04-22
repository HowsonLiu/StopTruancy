#pragma once

#include <QWidget>

class LeftWidget;
class EmptyWidget;
class StudentWidget;
class ClassWidget;
class NetworkWidget;
class MainWidget : public QWidget
{
	Q_OBJECT
private:
	NetworkWidget* m_networkWidget;
	LeftWidget* m_leftWidget;
	StudentWidget* m_studentWidget;
	ClassWidget* m_classWidget;
	EmptyWidget* m_emptyWidget;

public:
	MainWidget(QWidget *parent = Q_NULLPTR);
	~MainWidget();
	void TryConnect();

public slots:
	void onSelectStudent(const QString&);
	void onSelectClass(const QString&);
};