#include "circle.h"
#include <QImage>
#include <QDebug>

Circle::Circle(QObject *parent) :
    QObject(parent)
{
	radius = 20;
	x = 0;
	y = 0;
}

void Circle::Draw(QImage* pBackBuffer) {
    if (!pBackBuffer)
    {
        return;
    }
    uchar* pubBuffer = pBackBuffer->bits();
	if ((pBackBuffer->width() / 2) < (radius + std::abs(x)) ||
		(pBackBuffer->height() / 2) < (radius + std::abs(y))) {
        return;
    }
	int rsquare = radius * radius;
	int rsquaresquare = rsquare * rsquare;
	int x0 = radius;
	int dx = 0;
	int centerY = pBackBuffer->height() / 2 + y;
	int centerX = pBackBuffer->width() / 2 + x;
	int lineBytes = pBackBuffer->bytesPerLine();
	memset(pubBuffer + 3 *	(centerX - radius) + lineBytes * centerY, 333, sizeof(uchar) * 6 * radius);

	for (int y = 1; y <= radius; y++) {
		int x1 = x0 - (dx - 1);
		for (; x1 > 0; x1--) {
			if (x1 * x1 * rsquare + y * y * rsquare <= rsquaresquare)
				break;
		}
		dx = x0 - x1;
		x0 = x1;
		memset(pubBuffer + 3 * (centerX - x0) + lineBytes * (centerY - y), 333, sizeof(uchar) * 6 * x0);
		qDebug() << "start memset y : " << y;
		memset(pubBuffer + 3 * (centerX - x0) + lineBytes * (centerY + y), 333, sizeof(uchar) * 6 * x0);
		qDebug() << "end memset";
	}
}

void Circle::setParams(std::vector<int> params) {
	x = params.at(0);
	y = params.at(1);
	radius = params.at(2);
}
