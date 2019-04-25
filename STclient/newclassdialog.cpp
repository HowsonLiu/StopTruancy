#include "newclassdialog.h"
#include "Resources.h"
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>

NewClassDialog::NewClassDialog(QWidget* parent)
	: QDialog(parent)
{
	// create
	m_nameEdit = new QLineEdit(this);
	m_tipLabel = new QLabel(this);
	m_searchEdit = new QLineEdit(this);
	m_listView = new QListView(this);

	// name edit
	//QFont nameFont(g_defaultFont, )

	// search
	QPushButton* searchButton = new QPushButton(this);
	QHBoxLayout* searchLayout = new QHBoxLayout(this);
	searchButton->setStyleSheet("border-image:url(:/LeftWidget/Resources/search.png)");
	searchButton->setFixedSize(20, 20);
	searchLayout->setContentsMargins(0, 0, 0, 0);	// 外边距为0
	searchLayout->addWidget(searchButton, 0, Qt::AlignRight);	// 按钮右对齐
	m_searchEdit->setTextMargins(0, 0, searchButton->width(), 0);	// 字体不要在按钮上面
	m_searchEdit->setLayout(searchLayout);
}


NewClassDialog::~NewClassDialog()
{
}
