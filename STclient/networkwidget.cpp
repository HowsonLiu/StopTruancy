#include "networkwidget.h"
#include <QLabel>
#include <QPushButton>

NetworkWidget::NetworkWidget(QWidget *parent)
	: QWidget(parent)
{
	// create
	m_connectingLabel = new QLabel(this);
	m_disconnectedLabel = new QLabel(this);
	m_retryLabel = new QPushButton(this);
}


NetworkWidget::~NetworkWidget()
{
}
