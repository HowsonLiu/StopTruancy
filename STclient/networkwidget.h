#pragma once
#include <QWidget>

class NetworkWidget : public QWidget
{
	Q_OBJECT
public:
	NetworkWidget(QWidget *parent = Q_NULLPTR);
	~NetworkWidget();

private:
	QLabel* m_connectingLabel;
	QPushButton* m_retryLabel;
	QLabel* m_disconnectedLabel;
};

