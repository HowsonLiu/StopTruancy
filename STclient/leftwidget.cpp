#include "leftwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>

LeftWidget::LeftWidget(QWidget *parent)
	: QWidget(parent)
{
	// create
	m_signLabel = new QLabel(this);
	m_comboBox = new QComboBox(this);
	m_searchEdit = new QLineEdit(this);
	m_listView = new QListView(this);
	m_addButton = new QPushButton(this);
	m_delButton = new QPushButton(this);

	// layout
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_signLabel);
	mainLayout->addWidget(m_comboBox);
	mainLayout->addWidget(m_searchEdit);
	mainLayout->addWidget(m_listView);
	QHBoxLayout* buttonsLayout = new QHBoxLayout(this);
	buttonsLayout->addWidget(m_addButton);
	buttonsLayout->addWidget(m_delButton);
	mainLayout->addLayout(buttonsLayout);

	// signlabel
	QPixmap logo(":/MainWindows/Resources/logo.png");
	logo = logo.scaled(QSize(289, 175), Qt::KeepAspectRatio);
	m_signLabel->setPixmap(logo);

	// combobox
}


LeftWidget::~LeftWidget()
{
}
