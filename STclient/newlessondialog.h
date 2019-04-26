#pragma once
#include <QDialog>
#include <opencv2/face.hpp>

#define NEW_LESSON_OK 0
#define NEW_LESSON_ERROR_CLASS_NOT_EXIST -1
#define NEW_LESSON_ERROR_IMAGE_INVALID -2
#define NEW_LESSON_ERROR_DETECTION_XML_ERROR -3
#define NEW_LESSON_ERROR_TRAIN_ERROR -4

#define LESSON_PHOTO_MAX_WIDTH 1500
#define LESSON_PHTOT_MAX_HEIGHT 900

class QLabel;
class QListView;
class QPushButton;
class QImage;
class StudentsModel;
class NewLessonDialog : public QDialog
{
	Q_OBJECT
private:
	QLabel* m_photoLabel;
	QListView* m_listView;
	StudentsModel* m_studentsModel;
	QLabel* m_numLabel;
	QPushButton* m_forwardButton;
	QPushButton* m_backButton;
	QPushButton* m_okButton;

	QImage* m_originPhoto;
	QString m_className;
	int m_errorCode;

	cv::Mat m_originMat;
	cv::Mat m_gray;
	cv::CascadeClassifier m_cascade;
	cv::Ptr<cv::face::EigenFaceRecognizer> m_modelPCA;
	std::vector<cv::Rect> m_faceRect;
	std::vector<int> m_originResult;
	std::vector<int> m_customResult;

	int m_curIndex;
	QImage* m_showPhoto;

public:
	NewLessonDialog(const QString&, QImage*, QWidget* parent = nullptr);
	~NewLessonDialog();
	inline int getErrorCode() const { return m_errorCode; }

private:
	void Init();
	void Predict();
	void RectangleIndexFace(int);
};

