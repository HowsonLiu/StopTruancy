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
	m_lessonsModel = new LessonsModel(this);

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
	m_lessonList->setModel(m_lessonsModel);
	m_lessonList->setViewMode(QListView::IconMode);
	m_lessonList->setIconSize(QSize(150, 150));		// 按照较少的值按比例拉伸
	m_lessonList->setGridSize(QSize(180, 150));
	m_lessonList->setResizeMode(QListView::Adjust);	// 拉伸更新

	// attendance
	m_attendanceList->setModel(m_attendanceModel);
	m_attendanceList->setItemsExpandable(false);	// 不可展开
	m_attendanceList->setRootIsDecorated(false);	// 隐藏折叠三角形
	m_attendanceList->setHeaderHidden(true);
	m_attendanceList->setColumnHidden(CLASS_NAME_INDEX, true);	// 隐藏班级名字列

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_lessonList, &QListView::doubleClicked, this, &ClassWidget::onItemDoubleClick);
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
		m_lessonsModel->SetLessons(m_class->getLessons());
	}
	else {
		m_nameLabel->setText(m_defaultName);
		m_attendanceModel->SetAttendances(QList<Attendance>());
		m_lessonsModel->SetLessons(QList<Lesson>());
	}
}

QString ClassWidget::GetCurName() const
{
	return m_class ? m_class->getName() : QString();
}

void ClassWidget::onItemDoubleClick(const QModelIndex& index) 
{
	if (!index.isValid()) return;
	QPixmap big = m_lessonsModel->data(index, Qt::UserRole).value<QPixmap>();
	QLabel* bigLabel = new QLabel;
	bigLabel->setPixmap(big);
	bigLabel->show();
}