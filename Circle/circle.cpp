#include "circle.h"
#include <QImage>
#include <QDebug>
#include <cmath>

Circle::Circle(QObject *parent) :
	QObject(parent), params(new Params()) {}

void Circle::draw(QImage* pBackBuffer) {
	if (!pBackBuffer)
		return;
	uchar* pubBuffer = pBackBuffer->bits();
	qDebug() << "bytes : " << pBackBuffer->byteCount();
	pBackBuffer = pBackBuffer;
	r = 5;
	x0 = params->getX();
	y0 = params->getY();
	lineBytes = pBackBuffer->bytesPerLine();
	width = pBackBuffer->width();
	height = pBackBuffer->height();
	int maxindex = width * height - 1;
	ycenter = height / 2;
	xcenter = width / 2;


	int ystart = (y0 + r) > buf2coord(0).second ? buf2coord(0).second : y0 +r;
	int yend = buf2coord(maxindex).second > y0 - r ? buf2coord(maxindex).second : y0 - r;
	int yleft = buf2coord(0).first > x0 - r ? findIntersection(buf2coord(0).first) : y0;
	int yright = buf2coord(maxindex).first > x0 + r ? y0 : findIntersection(buf2coord(maxindex).first);
	int ymax = yleft < yright ? yright : yleft;
	int ymin = yleft == ymin ? yright : yleft;
	int xcurleft;
	int xcurright;
	auto circleEquation = [&](int y) {return sqrt(r * r - (y - y0) * (y - y0)) - x0;};
	qDebug() << "ystart : " << ystart << " yleft : " << yleft << " yright : " << yright;
	qDebug() << "buf2coord(0).first : " << buf2coord(0).first;
	qDebug() << "buf2coord(maxindex).first : " << buf2coord(maxindex).first;
	for (int y = ystart; y >= ymax; y--) {
		xcurright = circleEquation(y) + x0;
		xcurleft = 2 * x0 - xcurright;
		memset(pubBuffer + coord2buf(QPair<int, int>(xcurleft, y)), 333, sizeof(uchar) * (xcurright - xcurleft));
	}

//	if (!pBackBuffer) {
//		return;
//	}
//	uchar* pubBuffer = pBackBuffer->bits();
//	if ((pBackBuffer->width() / 2) < (r + std::abs(x)) || (pBackBuffer->height() / 2) < (r + std::abs(y))) {
//		return;
//	}

//	int rsquare = r * r;
//	int rsquaresquare = rsquare * rsquare;
//	int x0 = r;
//	int dx = 0;
//	int centerY = pBackBuffer->height() / 2 + y;
//	int centerX = pBackBuffer->width() / 2 + x;
//	int lineBytes = pBackBuffer->bytesPerLine();

//	memset(pubBuffer + 3 *	(centerX - r) + lineBytes * centerY, 333, sizeof(uchar) * 6 * r);

//	for (int y = 1; y <= r; y++) {
//		int x1 = x0 - (dx - 1);
//		for (; x1 > 0; x1--) {
//			if (x1 * x1 * rsquare + y * y * rsquare <= rsquaresquare)
//				break;
//		}
//		dx = x0 - x1;
//		x0 = x1;
//		memset(pubBuffer + 3 * (centerX - x0) + lineBytes * (centerY - y), 333, sizeof(uchar) * 6 * x0);
//		memset(pubBuffer + 3 * (centerX - x0) + lineBytes * (centerY + y), 333, sizeof(uchar) * 6 * x0);
//	}
}

void Circle::setParams(Params * params) {
	this->params = params;
}

QPair<int, int> Circle::buf2coord(int point) {
	return QPair<int, int> (point % width - xcenter, ycenter - point / height);
}

int Circle::coord2buf(QPair<int, int> coord) {
	return 3 * ((ycenter - coord.second) * width + xcenter + coord.first);
}

int Circle::findIntersection(int border) {
	int rootOf = r * r - (border - x0) * (border - x0);
	if (rootOf < 0)
		return -1;
	return sqrt(rootOf) - y0;
}
