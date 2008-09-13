#include "worker.h"
#include "renderoutput.h"
#include <core_api/scene.h>
#include <core_api/environment.h>
#include <core_api/imagefilm.h>
#include <yafraycore/xmlparser.h>

Worker::Worker(const char *filename, RenderOutput *output)
: QThread()
{
	m_file = filename;
	m_output = output;
	m_env = new yafray::renderEnvironment_t();
	m_scene = new yafray::scene_t();
	m_render = new yafray::paramMap_t();

	std::string ppath;
	if (m_env->getPluginPath(ppath))
		m_env->loadPlugins(ppath);
	
	bool success = parse_xml_file("yafaray.xml", m_scene, m_env, *m_render);
	if(!success) exit(1);

	int w=320, h=240;
	m_render->getParam("width", w); // width of rendered image
	m_render->getParam("height", h); // height of rendered image

	m_output->setRenderSize(QSize(w,h));
	
	if(! m_env->setupScene(*m_scene, *m_render, *m_output) ) 
		return;


}

void Worker::run()
{
	m_output->clear();
	m_scene->render();
}
