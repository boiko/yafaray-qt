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

#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

namespace Ui
{
class WindowBase;
}
class RenderOutput;
class Worker;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(const char *filename = 0);
	~MainWindow();

public slots:
	void render();
	void slotFinished();
	void slotEnableDisable(bool enable = true);
	void slotOpen();
	void slotSave();
	void slotSaveAs();
	void slotUseAlpha(int state);

private:
	Ui::WindowBase *m_ui;
	RenderOutput *m_output;
	Worker *m_worker;
	QString m_outputPath;
	QString m_lastPath;
};

#endif
