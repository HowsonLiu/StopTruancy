#include "leftwidget.h"
#include "facecollectionwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QResizeEvent>
#include <QMessageBox>
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

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_comboBox, QOverload<int>::of(&QComboBox::activated), this, &LeftWidget::onSwitchComboBox);	
	connect(m_addButton, &QPushButton::clicked, this, &LeftWidget::onAddButtonClick);

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
		int res = faceCollectionWidget.exec();
		if (res == QDialog::Accepted) {
			qDebug() << faceInfos.size() << endl;
		}
		else if(res == FACECOLLECTIONDIALOG_ERROR_CODE){
			QMessageBox::critical(this, "Can not open camera"
				, "Please check whether the computer contains a camera or whether the camera is occupied by other applications");
		}
	}
}
	
void LeftWidget::onSwitchComboBox(int index) 
{
	switch (index)
	{
	case 0:
		m_addButton->setStyleSheet("border-image:url(:/Student/Resources/user-add.png)");
		m_delButton->setStyleSheet("border-image:url(:/Student/Resources/user-delete.png)");
		break;
	case 1:
		m_addButton->setStyleSheet("border-image:url(:/Class/Resources/class-add.png)");
		m_delButton->setStyleSheet("border-image:url(:/Class/Resources/class-delete.png)");
		break;
	default:
		break;
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