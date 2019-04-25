#pragma once
#include <QDialog>

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

public:
	NewLessonDialog(const QString&, QImage*, QWidget* parent = nullptr);
	~NewLessonDialog();
};

