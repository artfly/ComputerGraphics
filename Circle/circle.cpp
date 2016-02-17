#include "circle.h"
#include <QImage>
#include <QDebug>

Circle::Circle(QObject *parent) :
	QObject(parent), params(new Params()) {}

void Circle::draw(QImage* pBackBuffer) {
	int r = params->getR();
	int x = params->getX();
	int y = params->getY();
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
	qWarning() << this->params->getX();
}
