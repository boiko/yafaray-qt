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

#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QString>

class RenderOutput;
namespace yafaray
{
class renderEnvironment_t;
class render_t;
class scene_t;
class paraMap_t;
}

class Worker : public QThread
{
	Q_OBJECT
public:
	Worker(const char *file, RenderOutput *output);
	void run();
private:
	RenderOutput *m_output;
	yafaray::renderEnvironment_t *m_env;
	yafaray::scene_t *m_scene;
	yafaray::paraMap_t *m_render;
	QString m_file;
	bool m_valid;
};

#endif
