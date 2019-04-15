#pragma once
#include <QWidget>

class QLabel;
class QPushButton;
class NetworkWidget : public QWidget
{
	Q_OBJECT

public:
	enum NetStatus {
		Connecting = 0,
		Offline
	};

public:
	NetworkWidget(QWidget *parent = Q_NULLPTR);
	~NetworkWidget();

private:
	QLabel* m_connectingLabel;
	QPushButton* m_retryButton;
	QLabel* m_offlineLabel;

	NetStatus m_status;

public:
	void SetNetStatus(NetStatus status);
};

