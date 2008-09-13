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

#ifndef RENDEROUTPUT_H
#define RENDEROUTPUT_H

#include <QWidget>
#include <QMutex>
#include <QImage>
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
	bool useAlpha();
	void setUseAlpha(bool use);
	QImage removeAlpha(const QImage &img);

protected:
	virtual void paintEvent(QPaintEvent *e);

private:
	QImage m_image;
	QMutex m_mutex;
	QMutex m_updateLock;
	bool m_alpha;
};

#endif
