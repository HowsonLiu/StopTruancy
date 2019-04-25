#include "newlessondialog.h"
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QLayout>

NewLessonDialog::NewLessonDialog(const QString& classname, QImage* image, QWidget* parent)
	: QDialog(parent)
	, m_className(classname)
	, m_photo(image)
{
	// create
	m_photoLabel = new QLabel(this);
	m_listView = new QListView(this);
	m_numLabel = new QLabel(this);
	m_forwardButton = new QPushButton(this);
	m_backButton = new QPushButton(this);
	m_okButton = new QPushButton(this);

	// layout
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_photoLabel);
	QVBoxLayout* rightLayout = new QVBoxLayout(this);
	rightLayout->addWidget(m_listView);
	QHBoxLayout* rightDownLayout = new QHBoxLayout(this);
	rightDownLayout->addWidget(m_numLabel);
	rightDownLayout->addWidget(m_forwardButton);
	rightDownLayout->addWidget(m_backButton);
	rightDownLayout->addWidget(m_okButton);
	rightLayout->addLayout(rightDownLayout);
	layout->addLayout(rightLayout);
	setLayout(layout);

	
}


NewLessonDialog::~NewLessonDialog()
{
}
