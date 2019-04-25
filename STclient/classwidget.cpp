#include "classwidget.h"
#include "Resources.h"
#include "mvd.h"
#include "newlessondialog.h"
#include <QVBoxLayout>
#include <QListView>
#include <QTreeView>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QListView>
#include <QMessageBox>
#include <QFileDialog>

ClassWidget::ClassWidget(QWidget *parent)
	: QWidget(parent)
	, m_class(nullptr)
	, m_defaultName("Null")
{
	// create
	m_nameLabel = new QLabel(this);
	m_trainButton = new QPushButton(this);
	m_trainLabel = new QLabel(this);
	m_addLessonLabel = new QLabel(this);
	m_addLessonButton = new QPushButton(this);
	m_lessonList = new QListView(this);
	m_attendanceList = new QTreeView(this);
	m_attendanceModel = new AttendancesModel(this);
	m_lessonsModel = new LessonsModel(this);

	// layout
	QVBoxLayout* layout = new QVBoxLayout(this);
	QHBoxLayout* topLayout = new QHBoxLayout(this);
	topLayout->addWidget(m_nameLabel);
	topLayout->addWidget(m_trainButton);
	topLayout->addWidget(m_trainLabel);
	topLayout->addStretch();
	layout->addLayout(topLayout);
	QHBoxLayout* midLayout = new QHBoxLayout(this);
	midLayout->addStretch();
	midLayout->addWidget(m_addLessonLabel);
	midLayout->addWidget(m_addLessonButton);
	layout->addLayout(midLayout);
	layout->addWidget(m_lessonList);
	layout->addWidget(m_attendanceList);
	setLayout(layout);

	// name
	m_nameLabel->setFont(QFont(g_defaultFont, g_defaultTitleFontSize, g_defaultTitleFontWeight));

	// train
	m_trainButton->setStyleSheet("border-image:url(:/Class/Resources/refresh.png)");
	m_trainButton->setFixedSize(QSize(20, 20));
	m_trainLabel->setFont(QFont(g_defaultFont, g_defaultTipFontSize, g_defaultTitleFontWeight));
	m_trainLabel->setText("Train!!");

	// add lesson
	m_addLessonLabel->setFont(QFont(g_defaultFont, g_defaultTipFontSize, g_defaultTitleFontWeight));
	m_addLessonLabel->setText("Add lessons");
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

	connect(m_lessonList, &QListView::doubleClicked, this, &ClassWidget::onLessonItemDoubleClick);
	connect(m_attendanceList, &QTreeView::doubleClicked, this, &ClassWidget::onAttendanceItemDoubleClick);
	connect(m_trainButton, &QPushButton::clicked, this, &ClassWidget::onTrainButtonClick);
	connect(m_addLessonButton, &QPushButton::clicked, this, &ClassWidget::onAddLessonButtonClick);
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

void ClassWidget::onLessonItemDoubleClick(const QModelIndex& index) 
{
	if (!index.isValid()) return;
	QPixmap big = m_lessonsModel->data(index, Qt::UserRole).value<QPixmap>();
	QLabel* bigLabel = new QLabel;
	bigLabel->setPixmap(big);
	bigLabel->show();
}

void ClassWidget::onAttendanceItemDoubleClick(const QModelIndex& index)
{
	if (!index.isValid()) return;
	QModelIndex curIndex = m_attendanceModel->index(index.row(), STUDENT_NAME_INDEX, index.parent());	// 计算同行stu列的index
	QString stuName = m_attendanceModel->data(curIndex, Qt::DisplayRole).toString();
	emit sigSelectStudent(stuName);
}

void ClassWidget::onTrainButtonClick()
{
	ClassSerializer serializer(m_class->getName());
	if (!serializer.Exist()) return;
	int res = serializer.Train();
	if (res == CS_OK) {
		QMessageBox::information(this, "Success", "Train successfully");
	}
	else if (res == CS_STUDENT_NOT_EXIST) {
		QMessageBox::critical(this, "Error", "This class has no students");
	}
	else if (res == CS_API_ERROR) {
		QMessageBox::critical(this, "Error", "OpenCV error");
	}
}

void ClassWidget::onAddLessonButtonClick()
{
	QString path = QFileDialog::getOpenFileName(this, "Upload a lesson photo"
		, "/", "Images(*.jpg *.png)");
	QImage photo;
	photo.load(path);
	NewLessonDialog newLessonDialog(m_class->getName(), &photo, this);
	int res = newLessonDialog.exec();
}
