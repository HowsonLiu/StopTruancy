#include "leftwidget.h"
#include "mvd.h"
#include "../STdatacenter/studentserializer.h"
#include "newclassdialog.h"
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QResizeEvent>
#include <QMessageBox>
#include <QModelIndex>
#include <QDebug>

LeftWidget::LeftWidget(QWidget *parent)
	: QWidget(parent)
{
	// create
	m_signLabel = new QLabel(this);
	m_comboBox = new QComboBox(this);
	m_searchEdit = new QLineEdit(this);
	m_listView = new QListView(this);
	m_addButton = new QPushButton(this);
	m_delButton = new QPushButton(this);
	m_allStudentsModel = new AllStudentsModel(this);
	m_allClassesModel = new AllClassesModel(this);
	DefaultStuAndClsDelegate* defaultDelegate = new DefaultStuAndClsDelegate(this);

	// layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_signLabel, 1, Qt::AlignCenter);
	mainLayout->addWidget(m_comboBox);
	mainLayout->addWidget(m_searchEdit);
	mainLayout->addWidget(m_listView, 5);
	QHBoxLayout* buttonsLayout = new QHBoxLayout(this);
	buttonsLayout->addWidget(m_addButton);
	buttonsLayout->addWidget(m_delButton);
	mainLayout->addLayout(buttonsLayout);

	// signlabel
	QPixmap logo(":/LeftWidget/Resources/logo.png");
	logo = logo.scaled(QSize(250, 65), Qt::KeepAspectRatio);
	m_signLabel->setPixmap(logo);

	// combobox
	m_comboBox->addItem("Student");
	m_comboBox->addItem("Class");

	// search
	QPushButton* searchButton = new QPushButton(this);
	QHBoxLayout* searchLayout = new QHBoxLayout(this);
	searchButton->setStyleSheet("border-image:url(:/LeftWidget/Resources/search.png)");
	searchButton->setFixedSize(20, 20);
	searchLayout->setContentsMargins(0, 0, 0, 0);	// 外边距为0
	searchLayout->addWidget(searchButton, 0, Qt::AlignRight);	// 按钮右对齐
	m_searchEdit->setTextMargins(0, 0, searchButton->width(), 0);	// 字体不要在按钮上面
	m_searchEdit->setLayout(searchLayout);

	// add and delete
	m_addButton->setFixedSize(50, 50);
	m_delButton->setFixedSize(50, 50);

	// listview
	m_listView->setItemDelegate(defaultDelegate);

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_comboBox, QOverload<int>::of(&QComboBox::activated), this, &LeftWidget::onSwitchComboBox);
	connect(m_addButton, &QPushButton::clicked, this, &LeftWidget::onAddButtonClick);
	connect(m_listView, &QListView::doubleClicked, this, &LeftWidget::onItemDoubleClick);
	connect(m_delButton, &QPushButton::clicked, this, &LeftWidget::onDelButtonClick);

	// init
	onSwitchComboBox(0);
}


LeftWidget::~LeftWidget()
{
}

void LeftWidget::onAddButtonClick()
{
	if (m_comboBox->currentIndex() == 0) {
		std::vector<cv::Mat> faceInfos;
		FaceCollectionDialog faceCollectionWidget(&faceInfos, this);
		int errorCode = faceCollectionWidget.getErrorCode();
		if (errorCode == FACE_COLLECTION_DIALOG_INVALID_PARAM) {
			QMessageBox::critical(this, "Source Code Error", "Invalid param");
		}
		else if (errorCode == CAMERA_WIDGET_FACE_DETECTION_XML_ERROR) {
			QMessageBox::critical(this, "Face Detection Error", "Can not find the detection xml");
		}
		else if (errorCode == FACE_COLLECTION_DIALOG_OK) {
			int res = faceCollectionWidget.exec();
			if (res == QDialog::Accepted) {
				QString name;
				NewStudentDialog newStudentDialog(&name, this);
				if (newStudentDialog.exec() == QDialog::Accepted) AddStudent(name, faceInfos);
			}
			else if (res == CAMERA_WIDGET_RUNTIME_ERROR) {
				QMessageBox::critical(this, "Can not open camera"
					, "Please check whether the computer contains a camera or whether the camera is occupied by other applications");
			}
		}
	}
	else if (m_comboBox->currentIndex() == 1) {
		QString className;
		std::vector<QString> studentNames;
		NewClassDialog newClassDialog(&className, &studentNames, this);
		int res = newClassDialog.exec();
		if (res == QDialog::Accepted) {
			AddClass(className, studentNames);
		}
	}
}

void LeftWidget::onDelButtonClick()
{
	if (m_comboBox->currentIndex() == 0) {
		DelStudent();
	}
	else if (m_comboBox->currentIndex() == 1) {
		DelClass();
	}
}

void LeftWidget::onSwitchComboBox(int index)
{
	switch (index)
	{
	case 0:
		m_listView->setModel(m_allStudentsModel);
		m_addButton->setStyleSheet("QPushButton{border-image:url(:/Student/Resources/student-add.png)}"
			"QPushButton:hover{border-image:url(:/Student/Resources/student-add-hover.png)}");
		m_delButton->setStyleSheet("QPushButton{border-image:url(:/Student/Resources/student-del.png)}"
			"QPushButton:hover{border-image:url(:/Student/Resources/student-del-hover.png)}");
		break;
	case 1:
		m_listView->setModel(m_allClassesModel);
		m_addButton->setStyleSheet("QPushButton{border-image:url(:/Class/Resources/class-add.png)}"
			"QPushButton:hover{border-image:url(:/Class/Resources/class-add-hover.png)}");
		m_delButton->setStyleSheet("QPushButton{border-image:url(:/Class/Resources/class-del.png)}"
			"QPushButton:hover{border-image:url(:/Class/Resources/class-del-hover.png)}");
		break;
	default:
		break;
	}
}

void LeftWidget::onItemDoubleClick(const QModelIndex& index)
{
	if (!index.isValid()) return;
	if (m_comboBox->currentIndex() == 0)
	{
		QString stuName = m_allStudentsModel->data(index).toString();
		emit sigSelectStudent(stuName);
	}
	else if (m_comboBox->currentIndex() == 1) {
		QString clsName = m_allClassesModel->data(index).toString();
		emit sigSelectClass(clsName);
	}
}

void LeftWidget::AddStudent(const QString& name, const std::vector<cv::Mat>& faces)
{
	m_allStudentsModel->insertRows(0, 1, QModelIndex());					// 先随便插入一个
	QModelIndex index = m_allStudentsModel->index(0, 0, QModelIndex());		// 拿出来改
	m_allStudentsModel->setData(index, name, Qt::DisplayRole);
	StudentSerializer stu(name);								// 更新后台数据
	stu.init();
	stu.writeImages(faces);
}

void LeftWidget::DelStudent()
{
	QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
	for (QModelIndex index : indexList) {
		if (!index.isValid()) continue;
		QString name = m_allStudentsModel->data(index).toString();
		StudentSerializer stu(name);
		if (stu.canDelete()) {
			stu.deletes();
			m_allStudentsModel->removeRows(index.row(), 1, QModelIndex());	// 没有排序，可以直接按照row来删除
			emit sigDelStudent(name);
		}
		else {
			QMessageBox::information(this, "Can not delete", "This student has a course that cannot be deleted");
		}
	}
}

void LeftWidget::AddClass(const QString& name, const std::vector<QString>& stuNames)
{
	m_allClassesModel->insertRows(0, 1, QModelIndex());					// 先随便插入一个
	QModelIndex index = m_allClassesModel->index(0, 0, QModelIndex());		// 拿出来改
	m_allClassesModel->setData(index, name, Qt::DisplayRole);
	ClassSerializer cls(name);								// 更新后台数据
	cls.init();
	for (auto stuName : stuNames) {
		cls.addStudent(stuName);
	}
}

void LeftWidget::DelClass()
{
	QModelIndexList indexList = m_listView->selectionModel()->selectedIndexes();
	for (QModelIndex index : indexList) {
		if (!index.isValid()) continue;
		QString name = m_allClassesModel->data(index).toString();
		ClassSerializer cls(name);
		cls.deletes();
		m_allClassesModel->removeRows(index.row(), 1, QModelIndex());	// 没有排序，可以直接按照row来删除
		emit sigDelClass(name);
	}
}

EmptyWidget::EmptyWidget(QWidget* parent)
	: QWidget(parent)
{
	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);
}

EmptyWidget::~EmptyWidget()
{

}