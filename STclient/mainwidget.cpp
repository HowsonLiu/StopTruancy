#include "mainwidget.h"
#include "leftwidget.h"
#include "studentwidget.h"
#include "classwidget.h"
#include <QSplitter>
#include <QLabel>
#include <QLayout>

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	// create
	m_leftWidget = new LeftWidget(this);
	m_studentWidget = new StudentWidget(this);
	m_classWidget = new ClassWidget(this);

	// layout
	QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(m_leftWidget);
	splitter->addWidget(m_studentWidget);
	splitter->addWidget(m_classWidget);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(splitter);	// ����Ҫ�����ŵ�layout���Ȼ������MainWidget��С����
	setLayout(layout);

	splitter->show();
}

MainWidget::~MainWidget()
{
}
