#include "renderoutput.h"

#include <QPainter>
#include <QPaintEvent>

RenderOutput::RenderOutput(QWidget *parent)
: QWidget(parent)
{
	// use a checkerboard background
	QPixmap pix(20,20);
	pix.fill(Qt::white);
	QPainter p(&pix);
	QColor c(200,200,200);
	p.fillRect(10,0,10,10, c);
	p.fillRect(0,10,10,10, c);

	QPalette pal = palette();
	pal.setBrush(QPalette::Window, pix);
	setPalette(pal);
}

RenderOutput::~RenderOutput()
{
}

void RenderOutput::setRenderSize(const QSize &s)
{
	m_image = QImage(s, QImage::Format_ARGB32);
	setMinimumSize(s);
	resize(s);
}

bool RenderOutput::putPixel(int x, int y, const float *c, int channels)
{
	int r=c[0] * 255, g=c[1] * 255,b= c[2] * 255, a;
	QColor color(r<=255?r:255, g<=255?g:255, b<=255?b:255);
	if (channels > 4)
	{
		a = c[4]*255;
		if (a > 255) a = 255;
		if (a < 0) a = 0;
		color.setAlpha(a);
	}
	m_image.setPixel(x,y, color.rgba());
	return true;
}

void RenderOutput::flush()
{
	update();
}

void RenderOutput::flushArea(int x0, int y0, int x1, int y1)
{
//	update(QRect(x0, y0, x1-x0, y1-y0));
	update();
}

void RenderOutput::paintEvent(QPaintEvent *e)
{
	QRect r = m_image.rect();
	r.moveCenter(rect().center());
	QPainter p(this);
	p.setClipRegion(e->region());
	p.setPen(Qt::black);
	p.setBrush(palette().window());
	p.drawRect(r);
	p.drawImage(r.topLeft(), m_image);
}

void RenderOutput::clear()
{
	if (m_image.isNull())
		return;
	
	m_image.fill(Qt::transparent);
	update();
	
}
