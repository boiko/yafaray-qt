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
	void slotEnable();

private:
	Ui::WindowBase *m_ui;
	RenderOutput *m_output;
	Worker *m_worker;
};

#endif
