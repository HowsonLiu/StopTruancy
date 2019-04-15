#include "networkwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QMovie>
#include <QStackedLayout>

NetworkWidget::NetworkWidget(QWidget *parent)
	: QWidget(parent), m_status(NetStatus::Offline)
{
	// create
	m_connectingLabel = new QLabel(this);
	m_offlineLabel = new QLabel(this);
	m_retryButton = new QPushButton(this);
	QWidget* m_maskWidget = new QWidget(this);
	QWidget* m_ctrlWidget = new QWidget(this);

	// layout
	QStackedLayout* layout = new QStackedLayout(this);
	layout->addWidget(m_ctrlWidget);
	layout->addWidget(m_maskWidget);
	layout->setStackingMode(QStackedLayout::StackAll);
	QVBoxLayout* ctrlLayout = new QVBoxLayout;
	ctrlLayout->addStretch();	// 弹簧居中
	ctrlLayout->addWidget(m_offlineLabel, 0, Qt::AlignCenter);
	ctrlLayout->setSpacing(15);
	ctrlLayout->addWidget(m_retryButton, 0, Qt::AlignCenter);
	ctrlLayout->addWidget(m_connectingLabel, 0, Qt::AlignCenter);
	ctrlLayout->addStretch();
	m_ctrlWidget->setLayout(ctrlLayout);
	setLayout(layout);

	// maskwidget
	m_maskWidget->setStyleSheet("background-color: rgba(255, 255, 255, 180);");

	// connecting
	QMovie* connectingGif = new QMovie(":/Network/Resources/loading.gif");
	connectingGif->start();
	connectingGif->setScaledSize(QSize(60, 60));
	m_connectingLabel->setMovie(connectingGif);

	// offline
	QPixmap *offlinePixmap = new QPixmap(":/Network/Resources/offline.png");
	*offlinePixmap = offlinePixmap->scaled(QSize(60, 60), Qt::KeepAspectRatio);
	m_offlineLabel->setPixmap(*offlinePixmap);
	m_retryButton->setText("Retry");

	connect(m_retryButton, &QPushButton::clicked, this, &NetworkWidget::onRetry);

	// init
	m_connectingLabel->hide();
}


NetworkWidget::~NetworkWidget()
{
}

void NetworkWidget::SetNetStatus(NetStatus status)
{
	m_status = status;
	if (m_status == NetStatus::Connecting) {
		m_offlineLabel->hide();
		m_retryButton->hide();
		m_connectingLabel->show();
	}
	else if (m_status == NetStatus::Offline) {
		m_connectingLabel->hide();
		m_retryButton->show();
		m_connectingLabel->show();
	}
}

void NetworkWidget::onRetry() {
	SetNetStatus(Connecting);
	// 交给网络组件做测试
}

void NetworkWidget::onConnectFailed()
{
	SetNetStatus(Offline);
}
