/*
 * Copyright 2008 Gustavo Pichorim Boiko <gustavo.boiko@kdemail.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "mywindow.h"
#include "worker.h"
#include "renderoutput.h"
#include "ui_windowbase.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QDir>
#include <QImageWriter>

MainWindow::MainWindow(const char *filename)
: QMainWindow()
{
	m_ui = new Ui::WindowBase();
	m_ui->setupUi(this);
	m_output = new RenderOutput(this);
	m_worker = new Worker(filename, m_output);
	
	m_ui->renderArea->setWidget(m_output);
	m_ui->renderArea->setBackgroundRole(QPalette::Dark);
	connect(m_ui->renderButton, SIGNAL(clicked()), this, SLOT(render()));
	connect(m_worker, SIGNAL(finished()), this, SLOT(slotFinished()));
	connect(m_ui->alphaCheck, SIGNAL(stateChanged(int)), this, SLOT(slotUseAlpha(int)));

	// actions
	connect(m_ui->actionOpen, SIGNAL(triggered(bool)),
		this, SLOT(slotOpen()));
	connect(m_ui->actionSave, SIGNAL(triggered(bool)),
		this, SLOT(slotSave()));
	connect(m_ui->actionSave_As, SIGNAL(triggered(bool)),
		this, SLOT(slotSaveAs()));
	connect(m_ui->actionQuit, SIGNAL(triggered(bool)),
		this, SLOT(close()));

	// disable saving actions until we have something to save
	//m_ui->actionSave->setEnabled(false);
	//m_ui->actionSave_As->setEnabled(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::render()
{
	slotEnableDisable(false);
	m_worker->start();
}

void MainWindow::slotFinished()
{
	slotEnableDisable(true);
}

void MainWindow::slotEnableDisable(bool enable)
{
	m_ui->renderButton->setEnabled(enable);
	//m_ui->actionSave->setEnabled(enable);
	//m_ui->actionSave_As->setEnabled(enable);
}

void MainWindow::slotOpen()
{
	if (m_lastPath.isNull())
		m_lastPath = QDir::currentPath();
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Yafaray Scene"), m_lastPath, tr("Yafaray Scenes (*.xml)"));

	if (m_worker->isRunning())
		m_worker->terminate();
	delete m_worker;
	m_worker = new Worker(fileName.toLatin1().data(), m_output);

	m_lastPath = QDir(fileName).absolutePath();
	slotEnableDisable(true);

	// disable the save and save as actions
	//m_ui->actionSave->setEnabled(false);
	//m_ui->actionSave_As->setEnabled(false);
}

void MainWindow::slotSave()
{
	if (m_outputPath.isNull())
	{
		slotSaveAs();
		return;
	}

	if (!m_output->saveImage(m_outputPath))
	{
		//TODO show an error message
	}
}

void MainWindow::slotSaveAs()
{
	QString formats;
	QList<QByteArray> formatList = QImageWriter::supportedImageFormats();
	foreach (QByteArray format, formatList)
		formats += " *." + QString(format);

	if (m_lastPath.isNull())
		m_lastPath = QDir::currentPath();

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), m_lastPath, tr("Images (%1)").arg(formats));
	if (!fileName.isNull())
	{
		if (m_output->saveImage(fileName))
		{
			m_outputPath = fileName;
		}
		// TODO: show error message on !saving
		m_lastPath = QDir(fileName).absolutePath();
	}
}

void MainWindow::slotUseAlpha(int state)
{
	bool alpha = (state == Qt::Checked);

	if (alpha != m_output->useAlpha())
		m_output->setUseAlpha(alpha);
}
