#include "circle.h"
#include <QImage>
#include <QDebug>
#include <cmath>

Circle::Circle(QObject *parent) :
	QObject(parent), params(new Params()) {}

void Circle::draw(QImage* pBackBuffer) {
	r = params->getR();
	int x = params->getX();
	int y = params->getY();
	lineBytes = pBackBuffer->bytesPerLine();
	width = pBackBuffer->width();
	height = pBackBuffer->height();

//	int ystart = (y0 + r) > buf2pair(0).first ? buf2pair(0).first : y0 +r;
//	int yend = (y0 - r) > buf2pair((width - 1) * (height - 1)).first ? buf2pair(0).first : y0 +r;
//	int yleft = findIntersection(buf2pair(0).second) > 0? findIntersection(buf2pair(0).second) : y0;
//	int yright = findIntersection(buf2pair(width - 1).second) > 0? findIntersection(buf2pair(width - 1).second) : y0;
//	int yfirst = yleft > yright? yleft : yright;
//	int ysecond = yfirst == yleft? yright : yleft;
//	int x;
//	auto circleEquation = [](int y) {return sqrt(r * r - (y - y0) * (y - y0)) - x0;};
//	for (int y = ystart; y > first; y--) {
//		x = circleEquation(y);
//	}
////	qDebug() << yrange;
//	qDebug() <<  ystart;
//	qDebug() << yright;

	if (!pBackBuffer) {
		return;
	}
	uchar* pubBuffer = pBackBuffer->bits();
	if ((pBackBuffer->width() / 2) < (r + std::abs(x)) || (pBackBuffer->height() / 2) < (r + std::abs(y))) {
		return;
	}

	int rsquare = r * r;
	int rsquaresquare = rsquare * rsquare;
	int x0 = r;
	int dx = 0;
	int centerY = pBackBuffer->height() / 2 + y;
	int centerX = pBackBuffer->width() / 2 + x;
	int lineBytes = pBackBuffer->bytesPerLine();

	memset(pubBuffer + 3 *	(centerX - r) + lineBytes * centerY, 333, sizeof(uchar) * 6 * r);

	for (int y = 1; y <= r; y++) {
		int x1 = x0 - (dx - 1);
		for (; x1 > 0; x1--) {
			if (x1 * x1 * rsquare + y * y * rsquare <= rsquaresquare)
				break;
		}
		dx = x0 - x1;
		x0 = x1;
		memset(pubBuffer + 3 * (centerX - x0) + lineBytes * (centerY - y), 333, sizeof(uchar) * 6 * x0);
		memset(pubBuffer + 3 * (centerX - x0) + lineBytes * (centerY + y), 333, sizeof(uchar) * 6 * x0);
	}
}

void Circle::setParams(Params * params) {
	this->params = params;
}

QPair<int, int> Circle::buf2pair(int point) {
	return QPair<int, int> (height / 2 - (point / height), (point % width) - width / 2);
}



int Circle::findIntersection(int border) {
	qDebug() << "border " << border;
	qDebug() << "x0 " << x0;
	int rootOf = r * r - (border - x0) * (border - x0);
	qDebug() << "rootOf" << rootOf;
	if (rootOf < 0)
		return -1;
	qDebug() << "return " << sqrt(rootOf) - y0;
	return sqrt(rootOf) - y0;
}
