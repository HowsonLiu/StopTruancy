#include "mainwidget.h"
#include "leftwidget.h"
#include "studentwidget.h"
#include "classwidget.h"
#include "networkwidget.h"
#include <QSplitter>
#include <QLabel>
#include <QStackedLayout>

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
	splitter->setStretchFactor(0, 0);	// ±ÈÀý
	splitter->setStretchFactor(1, 5);
	splitter->setStretchFactor(2, 5);
	splitter->setStretchFactor(3, 5);
	QStackedLayout* layout = new QStackedLayout(this);	// ÖØµþ·ÅÖÃ
	layout->setStackingMode(QStackedLayout::StackAll);
	layout->addWidget(m_networkWidget);
	layout->addWidget(splitter);
	setLayout(layout);

	// init
	m_studentWidget->hide();
	m_classWidget->hide();
	splitter->show();
	TryConnect();

	//test
	onSelectStudent();
}

MainWidget::~MainWidget()
{
}

void MainWidget::TryConnect()
{
	bool res = true;	// ÍøÂç²âÊÔ
	if (res) 
		m_networkWidget->hide();
	else
		m_networkWidget->show();
}

void MainWidget::onSelectStudent() 
{
	m_emptyWidget->hide();
	m_classWidget->hide();
	m_studentWidget->show();
	m_studentWidget->SetStudent(nullptr);
}