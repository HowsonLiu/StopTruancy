#include "newlessondialog.h"
#include "../STdatacenter/classserializer.h"
#include "../STdatacenter/datacenter.h"
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QLayout>

NewLessonDialog::NewLessonDialog(const QString& classname, QImage* image, QWidget* parent)
	: QDialog(parent)
	, m_className(classname)
	, m_photo(image)
	, m_errorCode(NEW_LESSON_OK)
{
	// create
	m_photoLabel = new QLabel(this);
	m_listView = new QListView(this);
	m_numLabel = new QLabel(this);
	m_forwardButton = new QPushButton(this);
	m_backButton = new QPushButton(this);
	m_okButton = new QPushButton(this);

	// layout
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_photoLabel);
	QVBoxLayout* rightLayout = new QVBoxLayout(this);
	rightLayout->addWidget(m_listView);
	QHBoxLayout* rightDownLayout = new QHBoxLayout(this);
	rightDownLayout->addWidget(m_numLabel);
	rightDownLayout->addWidget(m_forwardButton);
	rightDownLayout->addWidget(m_backButton);
	rightDownLayout->addWidget(m_okButton);
	rightLayout->addLayout(rightDownLayout);
	layout->addLayout(rightLayout);
	setLayout(layout);

	Init();
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
	if (!m_photo || m_photo->isNull()) {
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
