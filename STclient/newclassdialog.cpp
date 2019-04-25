#include "newclassdialog.h"
#include "Resources.h"
#include "../STdatacenter/classserializer.h"
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QLayout>
#include <QLabel>

NewClassDialog::NewClassDialog(QString* name, std::vector<QString>* studentNames, QWidget* parent)
	: QDialog(parent)
	, m_name(name)
	, m_studentNames(studentNames)
{
	// create
	m_nameEdit = new QLineEdit(this);
	m_tipLabel = new QLabel(this);
	m_searchEdit = new QLineEdit(this);
	m_listView = new QListView(this);
	m_numLabel = new QLabel(this);
	m_okButton = new QPushButton(this);

	// layout
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_nameEdit);
	layout->addWidget(m_tipLabel);
	layout->addWidget(m_searchEdit);
	layout->addWidget(m_listView);
	QHBoxLayout* btnLayout = new QHBoxLayout(this);
	btnLayout->addWidget(m_numLabel);
	btnLayout->addWidget(m_okButton);
	layout->addLayout(btnLayout);
	setLayout(layout);

	// name edit
	m_nameEdit->setFont(QFont(g_defaultFont, g_defaultTitleFontSize, g_defaultTitleFontWeight));

	// tip label
	m_tipLabel->setFont(QFont(g_defaultFont, g_defaultTipFontSize, g_defaultTitleFontWeight));
	m_tipLabel->setText("Already exists name");
	m_tipLabel->setStyleSheet("color:red");

	// search
	QPushButton* searchButton = new QPushButton(this);
	QHBoxLayout* searchLayout = new QHBoxLayout(this);
	searchButton->setStyleSheet("border-image:url(:/LeftWidget/Resources/search.png)");
	searchButton->setFixedSize(20, 20);
	searchLayout->setContentsMargins(0, 0, 0, 0);	// 外边距为0
	searchLayout->addWidget(searchButton, 0, Qt::AlignRight);	// 按钮右对齐
	m_searchEdit->setTextMargins(0, 0, searchButton->width(), 0);	// 字体不要在按钮上面
	m_searchEdit->setLayout(searchLayout);

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_nameEdit, &QLineEdit::textChanged, this, &NewClassDialog::onTextChanged);

	// init
	m_tipLabel->hide();
}


NewClassDialog::~NewClassDialog()
{
}

void NewClassDialog::onTextChanged(const QString& text)
{
	if (ClassSerializer(text).Exist()) {
		m_tipLabel->show();
		m_okButton->setEnabled(false);
	}
	else {
		m_tipLabel->hide();
		m_okButton->setEnabled(true);
	}
}