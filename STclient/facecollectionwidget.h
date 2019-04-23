#pragma once
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDialog>

#define COLLECT_NUMBER 20
#define SNAP_INTERVAL 2000
#define PAINT_INTERVAL 30
#define FACECOLLECTIONDIALOG_ERROR_CODE 2

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

public:
	FaceCollectionDialog(std::vector<cv::Mat>* faceInfos, QWidget* parent = nullptr);
	~FaceCollectionDialog();
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
	bool m_bInitError;
	cv::CascadeClassifier m_cascade;
	std::vector<cv::Rect> m_faceRect;

protected:
	virtual void paintEvent(QPaintEvent *event) override;

public:
	CameraWidget(QWidget* parent = nullptr);
	~CameraWidget();
	void GetCurrentFace(cv::Mat*);

signals:
	void sigCaptureError(int);
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

QImage Mat2QImage(const cv::Mat& src);
cv::Mat QImage2Mat(const QImage& src);