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

#include <core_api/scene.h>
#include <core_api/environment.h>
#include <core_api/imagefilm.h>
#include <yafraycore/xmlparser.h>
#include "worker.h"
#include "renderoutput.h"

Worker::Worker(const char *filename, RenderOutput *output)
: QThread()
{
	if (!filename)
	{
		m_valid = false;
		return;
	}

	m_file = filename;
	m_output = output;
	m_env = new yafaray::renderEnvironment_t();
	m_scene = new yafaray::scene_t();
	m_render = new yafaray::paraMap_t();

	std::string ppath;
	if (m_env->getPluginPath(ppath))
		m_env->loadPlugins(ppath);
	
	m_valid = parse_xml_file(filename, m_scene, m_env, *m_render);
	if(!m_valid) 
		return;

	int w=320, h=240;
	m_render->getParam("width", w); // width of rendered image
	m_render->getParam("height", h); // height of rendered image

	m_output->setRenderSize(QSize(w,h));
	
	if(! m_env->setupScene(*m_scene, *m_render, *m_output) ) 
		return;


}

void Worker::run()
{
	if (!m_valid)
		return;
	m_output->clear();
	m_scene->render();
}
