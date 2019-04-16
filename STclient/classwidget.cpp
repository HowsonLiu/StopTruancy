#include "classwidget.h"
#include "basestruct.h"
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ClassWidget::ClassWidget(QWidget *parent)
	: QWidget(parent)
	, m_class(nullptr)
	, m_defaultName("Null")
{
	// create
	m_nameLabel = new QLabel(this);
	m_addLessonButton = new QPushButton(this);
	m_lessonList = new QListView(this);
	m_attendanceList = new QListView(this);

	// layout
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_nameLabel);
	layout->addWidget(m_addLessonButton, 0, Qt::AlignRight);
	layout->addWidget(m_lessonList);
	layout->addWidget(m_attendanceList);
	setLayout(layout);

	// name
	m_nameLabel->setFont(QFont("Microsoft YaHei", 20, 75));

	// button
	m_addLessonButton->setStyleSheet("border-image:url(:/Student/Resources/add.png);");
	m_addLessonButton->setFixedSize(QSize(20, 20));

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);
}


ClassWidget::~ClassWidget()
{
}

void ClassWidget::SetClass(Class * cls)
{
	m_class = cls;
	if (m_class) {
		m_nameLabel->setText(cls->getName());
	}
	else {
		m_nameLabel->setText(m_defaultName);
	}
}
