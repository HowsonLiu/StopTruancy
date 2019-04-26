#pragma once
#include <QDialog>
#include <opencv2/face.hpp>

#define NEW_LESSON_OK 0
#define NEW_LESSON_ERROR_CLASS_NOT_EXIST -1
#define NEW_LESSON_ERROR_IMAGE_INVALID -2
#define NEW_LESSON_ERROR_DETECTION_XML_ERROR -3
#define NEW_LESSON_ERROR_TRAIN_ERROR -4

class QLabel;
class QListView;
class QPushButton;
class QImage;
class NewLessonDialog : public QDialog
{
	Q_OBJECT
private:
	QLabel* m_photoLabel;
	QListView* m_listView;
	QLabel* m_numLabel;
	QPushButton* m_forwardButton;
	QPushButton* m_backButton;
	QPushButton* m_okButton;

	QImage* m_photo;
	QString m_className;
	cv::CascadeClassifier m_cascade;
	std::vector<cv::Rect> m_faceRect;
	cv::Ptr<cv::face::EigenFaceRecognizer> m_modelPCA;

	int m_errorCode;

public:
	NewLessonDialog(const QString&, QImage*, QWidget* parent = nullptr);
	~NewLessonDialog();
	inline int getErrorCode() const { return m_errorCode; }

private:
	void Init();
};

