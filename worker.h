#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QString>

class RenderOutput;
namespace yafray
{
class renderEnvironment_t;
class render_t;
class paramMap_t;
class scene_t;
}


class Worker : public QThread
{
	Q_OBJECT
public:
	Worker(const char *file, RenderOutput *output);
	void run();
private:
	RenderOutput *m_output;
	yafray::renderEnvironment_t *m_env;
	yafray::scene_t *m_scene;
	yafray::paramMap_t *m_render;
	QString m_file;
	bool m_valid;
};

#endif
