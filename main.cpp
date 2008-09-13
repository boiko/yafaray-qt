#include "mywindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
	char *file = 0;
	QApplication app(argc, argv);

	if (argc > 1)
		file = argv[1];

	MainWindow w(file);
	w.show();
	if (file)
		w.render();

	return app.exec();
}
