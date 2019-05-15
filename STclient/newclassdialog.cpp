#include "newclassdialog.h"
#include "Resources.h"
#include "../STdatacenter/classserializer.h"
#include "mvd.h"
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QLayout>
#include <QLabel>

NewClassDialog::NewClassDialog(QString* name, std::vector<QString>* studentNames, QWidget* parent)
	: QDialog(parent)
	, m_name(name)
	, m_studentNames(studentNames)
	, bVaildName(false)
	, bVaildStudents(false)
{
	// create
	m_nameEdit = new QLineEdit(this);
	m_tipLabel = new QLabel(this);
	m_searchEdit = new QLineEdit(this);
	m_listView = new QListView(this);
	m_numLabel = new QLabel(this);
	m_okButton = new QPushButton(this);
	m_allStudentsModel = new AllStudentsModel(this);

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
	m_nameEdit->setPlaceholderText("Class Name");

	// tip label
	m_tipLabel->setFont(QFont(g_defaultFont, g_defaultTipFontSize, g_defaultTitleFontWeight));
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

	// listview
	m_listView->setModel(m_allStudentsModel);
	m_listView->setSelectionMode(QListView::MultiSelection);	// 多选
	DefaultStuAndClsDelegate* defaultDelegate = new DefaultStuAndClsDelegate(this);
	m_listView->setItemDelegate(defaultDelegate);

	// number label
	m_numLabel->setFont(QFont(g_defaultFont, 30, g_defaultTitleFontWeight));
	m_numLabel->setStyleSheet("color:red");

	// ok button
	m_okButton->setStyleSheet("border-image:url(:/Student/Resources/tick.png)");
	m_okButton->setFixedSize(QSize(30, 30));

	// background
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(pal);

	connect(m_nameEdit, &QLineEdit::textChanged, this, &NewClassDialog::onTextChanged);
	connect(m_listView, &QListView::clicked, this, &NewClassDialog::onItemClicked);
	connect(m_okButton, &QPushButton::clicked, this, &NewClassDialog::onPushButtonClicked);

	// init
	m_numLabel->setText("0");
	onTextChanged("");
}


NewClassDialog::~NewClassDialog()
{
}

void NewClassDialog::onItemClicked()
{
	int num = m_listView->selectionModel()->selectedIndexes().size();
	m_numLabel->setText(QString::number(num));
	bVaildStudents = num > 0;
	m_okButton->setEnabled(bVaildStudents && bVaildName);
}

void NewClassDialog::onPushButtonClicked()
{
	*m_name = m_nameEdit->text();
	QModelIndexList selectedList = m_listView->selectionModel()->selectedIndexes();
	for (QModelIndex curIndex : selectedList) {
		QString curStuName = m_allStudentsModel->data(curIndex, Qt::DisplayRole).toString();
		m_studentNames->push_back(curStuName);
	}
	accept();
}

void NewClassDialog::onTextChanged(const QString& text)
{
	if (text.isEmpty()) {
		m_tipLabel->setText("Name can't be empty");
		m_tipLabel->show();
		bVaildName = false;
		m_okButton->setEnabled(bVaildStudents && bVaildName);
		return;
	}
	if (ClassSerializer(text).exists()) {
		m_tipLabel->setText("Already exists name");
		m_tipLabel->show();
		bVaildName = false;
		m_okButton->setEnabled(bVaildStudents && bVaildName);
	}
	else {
		m_tipLabel->hide();
		bVaildName = true;
		m_okButton->setEnabled(bVaildStudents && bVaildName);
	}
}