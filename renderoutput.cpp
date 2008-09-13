#include "renderoutput.h"

#include <QPainter>

RenderOutput::RenderOutput(QWidget *parent)
: QWidget(parent)
{
}

RenderOutput::~RenderOutput()
{
}

void RenderOutput::setRenderSize(const QSize &s)
{
	m_image = QImage(s, QImage::Format_ARGB32);
}

bool RenderOutput::putPixel(int x, int y, const float *c, int channels)
{
	QColor color(c[0] * 255, c[1] * 255, c[2] * 255);
	//if (channels > 3)
	//	color.setAlpha(c[3] * 255);
	m_image.setPixel(x,y, color.rgba());
	return true;
}

void RenderOutput::flush()
{
	update();
}

void RenderOutput::flushArea(int x0, int y0, int x1, int y1)
{
	update();
}

void RenderOutput::paintEvent(QPaintEvent *e)
{
	QPainter p(this);
	p.drawImage(rect(), m_image);
}
