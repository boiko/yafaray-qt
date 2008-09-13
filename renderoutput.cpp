#include "renderoutput.h"

#include <QPainter>
#include <QPaintEvent>

RenderOutput::RenderOutput(QWidget *parent)
: QWidget(parent)
{
	m_alpha = true;

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
	m_mutex.lock();
	m_image.setPixel(x,y, color.rgba());
	m_mutex.unlock();
	return true;
}

void RenderOutput::flush()
{
	m_updateLock.lock();
	update();
	m_updateLock.unlock();
}

void RenderOutput::flushArea(int x0, int y0, int x1, int y1)
{
	m_updateLock.lock();
	QRect r(x0, y0, x1-x0, y1-y0), r2=m_image.rect();
	r2.moveCenter(rect().center());
	r.translate(r2.topLeft());
	update(r);
//	update();
	m_updateLock.unlock();
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
	if (m_alpha)
		p.drawImage(r.topLeft(), m_image);
	else
		p.drawImage(r.topLeft(), removeAlpha(m_image));
}

void RenderOutput::clear()
{
	if (m_image.isNull())
		return;
	
	m_image.fill(Qt::transparent);
	update();
	
}

bool RenderOutput::saveImage(const QString &path)
{
	if (m_alpha)
		return m_image.save(path);
	else
		return removeAlpha(m_image).save(path);
}

bool RenderOutput::useAlpha()
{
	return m_alpha;
}

void RenderOutput::setUseAlpha(bool use)
{
	m_updateLock.lock();
	m_alpha = use;
	update();
	m_updateLock.unlock();
}

QImage RenderOutput::removeAlpha(const QImage &img)
{
	return img.convertToFormat(QImage::Format_RGB32);
}
