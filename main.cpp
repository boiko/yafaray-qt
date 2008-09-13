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
