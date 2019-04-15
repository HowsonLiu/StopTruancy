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

	// layout
	QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(m_leftWidget);
	splitter->addWidget(m_studentWidget);
	splitter->addWidget(m_classWidget);
	QStackedLayout* layout = new QStackedLayout(this);	// ÖØµþ·ÅÖÃ
	layout->setStackingMode(QStackedLayout::StackAll);
	layout->addWidget(m_networkWidget);
	layout->addWidget(splitter);
	setLayout(layout);

	splitter->show();
}

MainWidget::~MainWidget()
{
}
