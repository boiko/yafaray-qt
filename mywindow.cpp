#include "mywindow.h"
#include "worker.h"
#include "renderoutput.h"
#include "ui_windowbase.h"

#include <QHBoxLayout>
#include <QScrollArea>

MainWindow::MainWindow(const char *filename)
: QMainWindow()
{
	m_ui = new Ui::WindowBase();
	m_ui->setupUi(this);
	m_output = new RenderOutput(this);
	m_worker = new Worker("yafaray.xml", m_output);
	
	m_ui->renderArea->setWidget(m_output);
	m_ui->renderArea->setBackgroundRole(QPalette::Dark);
	connect(m_ui->renderButton, SIGNAL(clicked()), this, SLOT(render()));
	connect(m_worker, SIGNAL(finished()), this, SLOT(slotEnable()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::render()
{
	m_ui->renderButton->setEnabled(false);
	m_worker->start();
}

void MainWindow::slotEnable()
{
	m_ui->renderButton->setEnabled(true);
}
