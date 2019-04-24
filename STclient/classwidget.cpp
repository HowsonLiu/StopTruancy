#include "classwidget.h"
#include "mvd.h"
#include <QVBoxLayout>
#include <QListView>
#include <QTreeView>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListView>

ClassWidget::ClassWidget(QWidget *parent)
	: QWidget(parent)
	, m_class(nullptr)
	, m_defaultName("Null")
{
	// create
	m_nameLabel = new QLabel(this);
	m_addLessonButton = new QPushButton(this);
	m_lessonList = new QListView(this);
	m_attendanceList = new QTreeView(this);
	m_attendanceModel = new AttendancesModel(this);

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

	// photo
	m_lessonList->setViewMode(QListView::IconMode);
	m_lessonList->setIconSize(QSize(100, 80));

	// attendance
	m_attendanceList->setModel(m_attendanceModel);
	m_attendanceList->setItemsExpandable(false);	// ����չ��
	m_attendanceList->setRootIsDecorated(false);	// �����۵�������
	m_attendanceList->setHeaderHidden(true);
	m_attendanceList->setColumnHidden(CLASS_NAME_INDEX, true);	// ���ذ༶������

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);
}


ClassWidget::~ClassWidget()
{
	if (m_class) delete m_class;
}

void ClassWidget::SetClass(Class* cls)
{
	if (m_class) delete m_class;
	m_class = cls;
	if (m_class) {
		m_nameLabel->setText(cls->getName());
		m_attendanceModel->SetAttendances(m_class->getAttendances());
	}
	else {
		m_nameLabel->setText(m_defaultName);
		m_attendanceModel->SetAttendances(QList<Attendance>());
	}
}

QString ClassWidget::GetCurName() const
{
	return m_class ? m_class->getName() : QString();
}
