#include "circle.h"
#include <QImage>
#include <QDebug>
#include <cmath>

Circle::Circle(QObject *parent) :
	QObject(parent), params(new Params()) {}

void Circle::draw(QImage* pBackBuffer) {
    if (!pBackBuffer) {
        return;
    }
    this->width = pBackBuffer->width();
    this->height = pBackBuffer->height();
    this->pubBuffer = pBackBuffer->bits();
    this->lineBytes = pBackBuffer->bytesPerLine();
    this->pBackBuffer = pBackBuffer;

    int r = params->getR();
    int centerY = height / 2 + params->getY();
    int centerX = width / 2 + params->getX();
    int rsquare = r * r;
    int x0 = r;
    int dx = 0;
    int x1 = 0;

    drawLine(centerX - r, centerX + r, centerY);
    for (int y = 1; y <= r; y++) {
        x1 = x0 - (dx - 1);
        for (; x1 > 0; x1--) {
            if (x1 * x1 + y * y <= rsquare) {
                break;
            }
        }
        dx = x0 - x1;
        x0 = x1;

        drawLine(centerX - x0, centerX + x0, centerY - y);
        drawLine(centerX - x0, centerX + x0, centerY + y);
    }
}

void Circle::drawLine(int xFrom, int xTo, int y) {
    if (y < 0 || y >= pBackBuffer->height()) {
        return;
    }
    if (xFrom < 0) {
        xFrom = 0;
    }
    if (xFrom >= pBackBuffer->width()) {
        xFrom = pBackBuffer->width() - 1;
    }
    if (xTo < 0) {
        xTo = 0;
    }
    if (xTo >= pBackBuffer->width()) {
        xTo = pBackBuffer->width() - 1;
    }
    memset(pubBuffer + 3 * xFrom + lineBytes * y, 0, sizeof(uchar) * 3 * (xTo - xFrom));
}

void Circle::setParams(Params * params) {
	this->params = params;
}
