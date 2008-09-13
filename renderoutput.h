#ifndef RENDEROUTPUT_H
#define RENDEROUTPUT_H

#include <QWidget>
#include <core_api/output.h>

class RenderOutput : public QWidget, public yafray::colorOutput_t
{
	Q_OBJECT
public:
	RenderOutput::RenderOutput(QWidget *parent = 0);
	~RenderOutput();

	void setRenderSize(const QSize &s);
	void clear();

	bool saveImage(const QString &path);

	// reimplemented from yafaray
	virtual bool putPixel(int x, int y, const float *c, int channels);
	void flush();
	virtual void flushArea(int x0, int y0, int x1, int y1);

protected:
	virtual void paintEvent(QPaintEvent *e);

private:
	QImage m_image;
};

#endif
