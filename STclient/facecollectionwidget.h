#pragma once
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDialog>

#define COLLECT_NUMBER 10
#define SNAP_INTERVAL 1000
#define PAINT_INTERVAL 30

#define FACE_COLLECTION_DIALOG_OK 0
#define FACE_COLLECTION_DIALOG_INVALID_PARAM -1
#define CAMERA_WIDGET_OK 0
#define CAMERA_WIDGET_FACE_DETECTION_XML_ERROR -2
#define CAMERA_WIDGET_RUNTIME_ERROR -3

class QTimer;
class CameraWidget;
class QLabel;
class FaceCollectionDialog : public QDialog
{
	Q_OBJECT
private:
	CameraWidget* m_cameraWidget;
	QLabel* m_label;
	QTimer* m_timer;

	int m_totalNum;
	int m_curNum;
	std::vector<cv::Mat>* m_faceInfos;
	int m_errorCode;

public:
	FaceCollectionDialog(std::vector<cv::Mat>* faceInfos, QWidget* parent = nullptr);
	~FaceCollectionDialog();
	inline int getErrorCode() const { return m_errorCode; }
	void UpdateLabel();

public slots:
	void onSnap();
};

class CameraWidget : public QWidget
{
	Q_OBJECT
private:
	cv::VideoCapture m_cap;
	cv::Mat m_frame;
	cv::Mat m_gray;
	QTimer* m_timer;
	int m_errorCode;
	cv::CascadeClassifier m_cascade;
	std::vector<cv::Rect> m_faceRect;

protected:
	virtual void paintEvent(QPaintEvent *event) override;

public:
	CameraWidget(QWidget* parent = nullptr);
	~CameraWidget();
	inline int getErrorCode() const { return m_errorCode; }
	void GetCurrentFace(cv::Mat*);

signals:
	void sigRuntimeError(int);
};

class QLineEdit;
class NewStudentDialog : public QDialog 
{
	Q_OBJECT
private:
	QLabel* m_nameLabel;
	QLineEdit* m_edit;
	QPushButton* m_button;
	QLabel* m_tipLabel;

	QString* m_name;
public:
	explicit NewStudentDialog(QString* name, QWidget* parent);
	~NewStudentDialog();

public slots:
	void onTextChanged(const QString&);
	void onEnterOrButtonClick();
};

// cv里面默认BGR， QImage里面默认RGB
QImage Mat2QImage(const cv::Mat& src);
cv::Mat QImage2Mat(const QImage& src);
QImage Mat2QImageEx(const cv::Mat& mat);
cv::Mat QImage2MatEx(const QImage& image);