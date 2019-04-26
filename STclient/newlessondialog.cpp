#include "newlessondialog.h"
#include "../STdatacenter/classserializer.h"
#include "../STdatacenter/datacenter.h"
#include "../STdatacenter/studentserializer.h"
#include "facecollectionwidget.h"
#include "Resources.h"
#include "mvd.h"
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>
#include <QDebug>

NewLessonDialog::NewLessonDialog(const QString& classname, QImage* image, QWidget* parent)
	: QDialog(parent)
	, m_className(classname)
	, m_originPhoto(image)
	, m_errorCode(NEW_LESSON_OK)
	, m_curIndex(0)
{
	// create
	m_photoLabel = new QLabel(this);
	m_listView = new QListView(this);
	m_studentsModel = new StudentsModel(this);
	m_numLabel = new QLabel(this);
	m_forwardButton = new QPushButton(this);
	m_backButton = new QPushButton(this);
	m_okButton = new QPushButton(this);
	m_showPhoto = new QImage;

	// layout
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_photoLabel);
	QVBoxLayout* rightLayout = new QVBoxLayout(this);
	rightLayout->addWidget(m_listView);
	QHBoxLayout* rightDownLayout = new QHBoxLayout(this);
	rightDownLayout->addWidget(m_numLabel);
	rightDownLayout->addWidget(m_backButton);
	rightDownLayout->addWidget(m_forwardButton);
	rightDownLayout->addWidget(m_okButton);
	rightLayout->addLayout(rightDownLayout);
	layout->addLayout(rightLayout);
	setLayout(layout);

	Init();
	if (m_errorCode != NEW_LESSON_OK) return;

	// image
	if (m_originPhoto->height() > LESSON_PHTOT_MAX_HEIGHT || m_originPhoto->width() > LESSON_PHOTO_MAX_WIDTH)
		*m_originPhoto = m_originPhoto->scaled(QSize(LESSON_PHOTO_MAX_WIDTH, LESSON_PHTOT_MAX_HEIGHT), Qt::KeepAspectRatio);

	// photo label
	m_photoLabel->setPixmap(QPixmap::fromImage(*m_originPhoto));

	// student list
	ClassSerializer(m_className).GetStudents(&m_stuList);
	m_studentsModel->SetStudents(m_stuList);
	m_listView->setModel(m_studentsModel);
	DefaultStuAndClsDelegate* defaultDelegate = new DefaultStuAndClsDelegate(this);
	m_listView->setItemDelegate(defaultDelegate);
	m_listView->setSelectionMode(QListView::MultiSelection);

	// num label
	m_numLabel->setFont(QFont(g_defaultFont, 30, g_defaultTitleFontWeight));
	m_numLabel->setStyleSheet("color:red");

	// buttons
	m_forwardButton->setStyleSheet("border-image:url(:/Class/Resources/forward.png)");
	m_forwardButton->setFixedSize(QSize(20, 20));
	m_backButton->setStyleSheet("border-image:url(:/Class/Resources/back.png)");
	m_backButton->setFixedSize(QSize(20, 20));

	Predict();
	m_numLabel->setText(QString::number(m_faceRect.size()));
	SetUp();

	connect(m_forwardButton, &QPushButton::clicked, this, &NewLessonDialog::onForwardButtonClicked);
	connect(m_backButton, &QPushButton::clicked, this, &NewLessonDialog::onBackButtonClicked);
}


NewLessonDialog::~NewLessonDialog()
{
}

void NewLessonDialog::Init()
{
	ClassSerializer serializer(m_className);
	if (!serializer.Exist()) {
		m_errorCode = NEW_LESSON_ERROR_CLASS_NOT_EXIST;
		return;
	}
	if (!m_originPhoto || m_originPhoto->isNull()) {
		m_errorCode = NEW_LESSON_ERROR_IMAGE_INVALID;
		return;
	}
	if (!m_cascade.load(DATA_CENTER_INSTANCE->getFaceDetectionXmlPath().toStdString())) {
		m_errorCode = NEW_LESSON_ERROR_DETECTION_XML_ERROR;
		return;
	}
	try {
		m_modelPCA = cv::face::EigenFaceRecognizer::create();
		m_modelPCA->read(serializer.getXmlPath().toStdString());	
	}
	catch (std::exception& e) {
		m_errorCode = NEW_LESSON_ERROR_TRAIN_ERROR;
		return;
	}
	m_errorCode = NEW_LESSON_OK;
}

void NewLessonDialog::Predict()
{
	m_originMat = QImage2MatEx(*m_originPhoto);
	cv::cvtColor(m_originMat, m_gray, CV_BGR2GRAY);
	cv::equalizeHist(m_gray, m_gray);
	m_cascade.detectMultiScale(m_gray, m_faceRect, 1.1f, 3, CV_HAAR_SCALE_IMAGE, cv::Size(100, 100));
	cv::Mat face;
	auto it = m_faceRect.begin();
	while (it != m_faceRect.end()) {
		if (it->height > 0 && it->width > 0) {
			face = m_gray(*it);
			if (face.rows >= 112) cv::resize(face, face, cv::Size(TRAIN_RESIZE_WIDTH, TRAIN_RESIZE_HEIGHT));
			int res = 0;
			try {
				res = m_modelPCA->predict(face);
			}
			catch (std::exception& e) {
				it = m_faceRect.erase(it);
				continue;
			}
			m_originResult.push_back(res);
			it++;
		}
		else {
			it = m_faceRect.erase(it);
		}
	}
	m_customResult = m_originResult;
}

void NewLessonDialog::SetUp()
{
	if (m_faceRect.size() <= 0) {
		m_forwardButton->setEnabled(false);
		m_backButton->setEnabled(false);
		m_listView->setSelectionMode(QListView::NoSelection);
	}
	else {
		RectangleIndexFace();
	}
}

void NewLessonDialog::RectangleIndexFace()
{
	if (m_curIndex < 0 || m_curIndex >= m_faceRect.size()) return;
	cv::Mat showMat = m_originMat.clone();
	cv::rectangle(showMat, m_faceRect[m_curIndex], cv::Scalar(0, 255, 0), 1, 8, 0);
	*m_showPhoto = Mat2QImage(showMat);
	m_photoLabel->setPixmap(QPixmap::fromImage(*m_showPhoto));
}

void NewLessonDialog::AutoSelectStudent()
{
	m_listView->clearSelection();
	if (m_customResult[m_curIndex] == -1) return;
	QString stuName = QString::number(m_customResult[m_curIndex]);
	int row = m_stuList.indexOf(stuName);
	QModelIndex index = m_studentsModel->index(row, 0, QModelIndex());
	m_listView->setCurrentIndex(index);
}

bool NewLessonDialog::SaveChanges()
{
	QModelIndexList selectList = m_listView->selectionModel()->selectedIndexes();
	if (selectList.size() <= 0) {
		m_customResult[m_curIndex] = -1;
	}
	else if (selectList.size() == 1) {
		QString stuName = selectList[0].data(Qt::DisplayRole).toString();
		m_customResult[m_curIndex] = stuName.toInt();
	}
	else {
		QMessageBox::critical(this, "Error", "A face can not belong to 2 person");
		return false;
	}
	return true;
}

void NewLessonDialog::onForwardButtonClicked()
{
	if (!SaveChanges()) return;
	if (m_curIndex >= m_faceRect.size() - 1) {
		m_forwardButton->setEnabled(false);
		return;
	}
	if (++m_curIndex > 0) m_backButton->setEnabled(true);
	RectangleIndexFace();
	AutoSelectStudent();
}

void NewLessonDialog::onBackButtonClicked()
{
	if (!SaveChanges()) return;
	if (m_curIndex <= 0) {
		m_backButton->setEnabled(false);
		return;
	}
	if (--m_curIndex < m_faceRect.size() - 1) m_forwardButton->setEnabled(true);
	RectangleIndexFace();
	AutoSelectStudent();
}

void NewLessonDialog::onOkButtonClicked()
{
	if (!SaveChanges()) return;
}
