#include "studentwidget.h"
#include "Resources.h"
#include "mvd.h"
#include "facecollectionwidget.h"
#include "../STdatacenter/studentserializer.h"
#include <opencv2/opencv.hpp>
#include <QMessageBox>
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
	m_optimizeLabel = new QLabel(this);
	m_optimizeButton = new QPushButton(this);
	m_attendancesList = new QListView(this);
	m_attendancesModel = new AttendancesModel(this);

	// layout
	QVBoxLayout* layout = new QVBoxLayout(this);
	QHBoxLayout* topLayout = new QHBoxLayout(this);
	topLayout->addSpacing(10);
	topLayout->addWidget(m_photoLabel);
	topLayout->addSpacing(10);
	topLayout->addWidget(m_nameLabel);
	topLayout->addStretch();
	QHBoxLayout* midLayout = new QHBoxLayout(this);
	midLayout->addWidget(m_optimizeLabel);
	midLayout->addWidget(m_optimizeButton);
	midLayout->addStretch();
	layout->addLayout(topLayout);
	layout->addSpacing(10);
	layout->addLayout(midLayout);
	layout->addSpacing(10);
	layout->addWidget(m_attendancesList);
	setLayout(layout);

	// name
	m_nameLabel->setFont(QFont(g_defaultFont, g_defaultTitleFontSize, g_defaultTitleFontWeight));

	// optimize
	m_optimizeLabel->setFont(QFont(g_defaultFont, 10, 75));
	m_optimizeLabel->setText("Recognition is not accurate? Let's optimize!");
	m_optimizeButton->setStyleSheet("border-image:url(:/Student/Resources/add.png);");
	m_optimizeButton->setFixedSize(QSize(20, 20));

	// list
	m_attendancesList->setModel(m_attendancesModel);
	ClassAttendanceDelegate* clsAttendanceDelegate = new ClassAttendanceDelegate(this);
	m_attendancesList->setItemDelegate(clsAttendanceDelegate);

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_optimizeButton, &QPushButton::clicked, this, &StudentWidget::onOptimizeButtonClick);
	connect(m_attendancesList, &QListView::doubleClicked, this, &StudentWidget::onItemDoubleClick);
}


StudentWidget::~StudentWidget()
{
	if (m_student) delete m_student;
}

void StudentWidget::SetStudent(Student* stu)
{
	if (m_student) delete m_student;
	m_student = stu;
	if (m_student) {
		m_photoLabel->setPixmap(m_student->getPhoto());
		m_nameLabel->setText(m_student->getName());
		m_attendancesModel->SetAttendances(m_student->getAttendances());
	}
	else {
		m_photoLabel->setPixmap(m_defaultPhoto);
		m_nameLabel->setText(m_defaultName);
		m_attendancesModel->SetAttendances(QList<Attendance>());
	}
}

QString StudentWidget::GetCurName() const
{
	return m_student ? m_student->getName() : QString();
}

void StudentWidget::onItemDoubleClick(const QModelIndex& index)
{
	if (!index.isValid()) return;
	QModelIndex curIndex = m_attendancesModel->index(index.row(), 0, index.parent());
	QString clsName = m_attendancesModel->data(curIndex, Qt::UserRole + CLASS_NAME_INDEX).toString();
	emit sigSelectClass(clsName);
}

void StudentWidget::onOptimizeButtonClick()
{
	std::vector<cv::Mat> faceInfos;
	FaceCollectionDialog faceCollectionWidget(&faceInfos, this);
	if (faceCollectionWidget.exec() == QDialog::Accepted) {
		StudentSerializer stu(m_student->getName());	
		if(stu.exists()) stu.writeImages(faceInfos);
		QMessageBox::information(this, "Success", "Optimized successfully");
	}
}