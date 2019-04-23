#include "mainwidget.h"
#include "leftwidget.h"
#include "studentwidget.h"
#include "classwidget.h"
#include "networkwidget.h"
#include "../STdatacenter/studentserializer.h"
#include "../STdatacenter/classserializer.h"
#include "basestruct.h"
#include <QSplitter>
#include <QLabel>
#include <QStackedLayout>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	// create
	m_networkWidget = new NetworkWidget(this);
	m_leftWidget = new LeftWidget(this);
	m_studentWidget = new StudentWidget(this);
	m_classWidget = new ClassWidget(this);
	m_emptyWidget = new EmptyWidget(this);

	// layout
	QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(m_leftWidget);
	splitter->addWidget(m_emptyWidget);
	splitter->addWidget(m_studentWidget);
	splitter->addWidget(m_classWidget);
	splitter->setStretchFactor(0, 0);	// ��಻��������
	splitter->setStretchFactor(1, 5);
	splitter->setStretchFactor(2, 5);
	splitter->setStretchFactor(3, 5);
	QStackedLayout* layout = new QStackedLayout(this);	// �ص�����
	layout->setStackingMode(QStackedLayout::StackAll);
	layout->addWidget(m_networkWidget);
	layout->addWidget(splitter);
	setLayout(layout);

	// init
	m_studentWidget->hide();
	m_classWidget->hide();
	splitter->show();
	TryConnect();

	connect(m_leftWidget, &LeftWidget::sigSelectClass, this, &MainWidget::onSelectClass);
	connect(m_leftWidget, &LeftWidget::sigSelectStudent, this, &MainWidget::onSelectStudent);

}

MainWidget::~MainWidget()
{
}

void MainWidget::TryConnect()
{
	bool res = true;	// �������
	if (res) 
		m_networkWidget->hide();
	else
		m_networkWidget->show();
}

void MainWidget::onSelectClass(const QString& name)
{
	ClassSerializer serializer(name);
	if (serializer.Exist()) {
		Class* cls = new Class(name);
		m_classWidget->SetClass(cls);
	}
	else {
		QMessageBox::critical(this, "Error", "Failed to read class information");
		return;
	}
	m_emptyWidget->hide();
	m_studentWidget->hide();
	m_classWidget->show();	
}

void MainWidget::onSelectStudent(const QString& name) 
{
	StudentSerializer serializer(name);
	if (serializer.Exist()) {
		Student* stu = new Student(name);
		m_studentWidget->SetStudent(stu);
	}
	else {
		QMessageBox::critical(this, "Error", "Failed to read student information");
		return;
	}
	m_emptyWidget->hide();
	m_classWidget->hide();
	m_studentWidget->show();
}