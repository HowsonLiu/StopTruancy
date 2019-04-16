#include "studentwidget.h"
#include "basestruct.h"
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QBoxLayout>

StudentWidget::StudentWidget(QWidget *parent)
	: QWidget(parent)
	, m_student(nullptr)
	, m_defaultPhoto(QPixmap(":/Student/Resources/defalut_student_photo.png"))
	, m_defaultName("Null")
{
	// create
	m_photoLabel = new QLabel(this);
	m_nameLabel = new QLabel(this);
	m_optimizeButton = new QPushButton(this);
	m_attendancesList = new QListView(this);

	// layout
	QVBoxLayout* layout = new QVBoxLayout(this);
	QHBoxLayout* topLayout = new QHBoxLayout(this);
	topLayout->addSpacing(10);
	topLayout->addWidget(m_photoLabel);
	topLayout->addSpacing(10);
	topLayout->addWidget(m_nameLabel);
	topLayout->addStretch();
	layout->addLayout(topLayout);
	QHBoxLayout* midLayout = new QHBoxLayout(this);
	midLayout->addWidget(m_optimizeButton);
	midLayout->addStretch();
	layout->addLayout(midLayout);
	layout->addWidget(m_attendancesList);
	setLayout(layout);

	// photo
	m_photoLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	// name
	m_nameLabel->setFont(QFont("Microsoft YaHei", 20, 75));

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);
}


StudentWidget::~StudentWidget()
{
}

void StudentWidget::SetStudent(Student* stu)
{
	m_student = stu;
	if (m_student) {
		m_photoLabel->setPixmap(m_student->getPhoto());
		m_nameLabel->setText(m_student->getName());
	}
	else {
		m_photoLabel->setPixmap(m_defaultPhoto);
		m_nameLabel->setText(m_defaultName);
		
	}
}
