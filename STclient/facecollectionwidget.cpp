#include "facecollectionwidget.h"
#include "Resources.h"
#include "../STdatacenter/studentserializer.h"
#include "../STdatacenter/datacenter.h"
#include <QTimer>
#include <QMessageBox>
#include <QPainter>
#include <QStackedLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

FaceCollectionDialog::FaceCollectionDialog(std::vector<cv::Mat>* faceInfos, QWidget* parent)
	: QDialog(parent)
	, m_faceInfos(faceInfos)
	, m_totalNum(COLLECT_NUMBER)
	, m_curNum(0)
{
	// create
	m_cameraWidget = new CameraWidget(this);
	m_label = new QLabel(this);
	m_timer = new QTimer(this);
	m_timer->setInterval(SNAP_INTERVAL);

	// layout
	QStackedLayout* layout = new QStackedLayout(this);
	layout->setStackingMode(QStackedLayout::StackAll);
	QWidget* uiWidget = new QWidget(this);
	QHBoxLayout* uiLayout = new QHBoxLayout(this);
	uiLayout->addStretch();
	uiLayout->addWidget(m_label, 0, Qt::AlignTop);
	uiWidget->setLayout(uiLayout);
	layout->addWidget(uiWidget);
	layout->addWidget(m_cameraWidget);
	setLayout(layout);

	// label
	m_label->setFont(QFont(g_defaultFont, 20, 75));
	m_label->setStyleSheet("color:green");

	connect(m_cameraWidget, &CameraWidget::sigRuntimeError, this, &FaceCollectionDialog::done);
	connect(m_timer, &QTimer::timeout, this, &FaceCollectionDialog::onSnap);

	// error check
	if (!m_faceInfos) {
		m_errorCode = FACE_COLLECTION_DIALOG_INVALID_PARAM;
		return;
	}
	m_errorCode = m_cameraWidget->getErrorCode();
	if (m_errorCode != CAMERA_WIDGET_OK) return;

	UpdateLabel();
	m_timer->start();
	resize(650, 480);	// 初始化大小
}


FaceCollectionDialog::~FaceCollectionDialog()
{
}

void FaceCollectionDialog::UpdateLabel()
{
	QString showText("%1/%2");
	showText = showText.arg(QString::number(m_curNum)).arg(QString::number(m_totalNum));
	m_label->setText(showText);
}

void FaceCollectionDialog::onSnap()
{
	cv::Mat mat;
	m_cameraWidget->GetCurrentFace(&mat);
	if (!mat.empty()) {
		m_faceInfos->push_back(mat.clone());
		m_curNum = m_faceInfos->size();
		UpdateLabel();
		if (m_curNum >= m_totalNum) {
			m_timer->stop();	// 不停止的话会很多次
			accept();
		}
	}
}

CameraWidget::CameraWidget(QWidget* parent)
	: QWidget(parent)
	, m_errorCode(CAMERA_WIDGET_OK)
{
	// create
	m_timer = new QTimer(this);
	m_timer->setInterval(PAINT_INTERVAL);

	connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&CameraWidget::update));

	// init
	m_cap.open(0);
	m_cascade.load(DATA_CENTER_INSTANCE->getFaceDetectionXmlPath().toStdString());
	if (m_cap.isOpened() && !m_cascade.empty())
		m_timer->start();
	else {
		m_errorCode = CAMERA_WIDGET_FACE_DETECTION_XML_ERROR;
	}
}

CameraWidget::~CameraWidget()
{
	m_cap.release();
	m_timer->stop();
}

void CameraWidget::GetCurrentFace(cv::Mat* mat)
{
	if (m_faceRect.empty()) return;
	*mat = cv::Mat(m_frame, m_faceRect[0]).clone();
}

void CameraWidget::paintEvent(QPaintEvent* event)
{
	if (!m_errorCode) m_cap >> m_frame;
	QPainter painter(this);
	if (!m_frame.empty()) {
		cv::cvtColor(m_frame, m_gray, CV_BGR2GRAY);	// 转灰度图
		cv::equalizeHist(m_gray, m_gray);	// 直方图均衡化，简单点来说就是提高对比度
		m_cascade.detectMultiScale(m_gray, m_faceRect,
			1.1f,	// 图像金字塔按照1.1的比例缩放
			3,	// 默认3个矩形框同时存在才算匹配成功
			CV_HAAR_SCALE_IMAGE		// 缩放图片而不是缩放分类器
			| CV_HAAR_FIND_BIGGEST_OBJECT,	// 只检测最大物体
			cv::Size(100, 100));
		for (size_t i = 0; i < m_faceRect.size(); ++i) {
			cv::rectangle(m_frame, m_faceRect[i], cv::Scalar(0, 255, 0), 1, 8, 0);
		}
		QImage img = Mat2QImage(m_frame);
		painter.drawImage(this->rect(), img);
	}
	else {
		m_errorCode = CAMERA_WIDGET_RUNTIME_ERROR;	// 这种情况是摄像头被占用
		painter.drawText(this->width() / 2, this->height() / 2, "Something error");
		emit sigRuntimeError(CAMERA_WIDGET_RUNTIME_ERROR);
	}
}

QImage Mat2QImage(const cv::Mat & src)
{
	cv::Mat temp; // make the same cv::Mat
	cvtColor(src, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need
	QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	dest.bits(); // enforce deep copy, see documentation 
	// of QImage::QImage ( const uchar * data, int width, int height, Format format )
	return dest;
}

cv::Mat QImage2Mat(const QImage & src)
{
	cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
	cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
	cvtColor(tmp, result, CV_BGR2RGB);
	return result;
}

QImage Mat2QImageEx(const cv::Mat & mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1  
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)  
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat  
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		return QImage();
	}
}

cv::Mat QImage2MatEx(const QImage & image)
{
	cv::Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

NewStudentDialog::NewStudentDialog(QString* name, QWidget* parent)
	: QDialog(parent)
	, m_name(name)
{
	// create
	m_nameLabel = new QLabel(this);
	m_edit = new QLineEdit(this);
	m_button = new QPushButton(this);
	m_tipLabel = new QLabel(this);

	// layout
	QVBoxLayout* layout = new QVBoxLayout;
	QHBoxLayout* midLayout = new QHBoxLayout;
	midLayout->addWidget(m_edit);
	midLayout->addWidget(m_button);
	layout->addWidget(m_nameLabel);
	layout->addLayout(midLayout);
	layout->addWidget(m_tipLabel);
	setLayout(layout);

	// name label
	m_nameLabel->setFont(QFont(g_defaultFont, g_defaultTitleFontSize, g_defaultTitleFontWeight));
	m_nameLabel->setText("Student's name");

	// button
	m_button->setStyleSheet("border-image:url(:/Student/Resources/tick.png)");
	m_button->setFixedSize(15, 15);

	// tips label
	m_tipLabel->setFont(QFont(g_defaultFont, g_defaultTipFontSize, g_defaultTitleFontWeight));
	m_tipLabel->setText("Already exists name");
	m_tipLabel->setStyleSheet("color:red");

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_button, &QPushButton::clicked, this, &NewStudentDialog::onEnterOrButtonClick);
	connect(m_edit, &QLineEdit::returnPressed, this, &NewStudentDialog::onEnterOrButtonClick);
	connect(m_edit, &QLineEdit::textChanged, this, &NewStudentDialog::onTextChanged);

	// init
	m_tipLabel->hide();
}

NewStudentDialog::~NewStudentDialog()
{
}

void NewStudentDialog::onEnterOrButtonClick()
{
	if (StudentSerializer(m_edit->text()).exists()) return;
	if (m_name) *m_name = m_edit->text();
	accept();
}

void NewStudentDialog::onTextChanged(const QString& text)
{
	if (StudentSerializer(text).exists()) {
		m_tipLabel->show();
		m_button->setEnabled(false);
	}
	else {
		m_tipLabel->hide();
		m_button->setEnabled(true);
	}
}