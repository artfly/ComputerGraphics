#include "lemniscate.h"
#include <QImage>
#include <iostream>
#include <QDebug>
#include <cmath>
#include <climits>

Lemniscate::Lemniscate(QObject *parent) :
	QObject(parent), params(new Params()) {}

void Lemniscate::draw(QImage * pBackBuffer) {
    if (!pBackBuffer)
		return;
    width = pBackBuffer->width();
    height = pBackBuffer->height();
    lineBytes = pBackBuffer->bytesPerLine();
    pubBuffer = pBackBuffer->bits();
    this->pBackBuffer = pBackBuffer;
	QPoint F1{params->getX1(), params->getY1()};
	QPoint F2{params->getX2(), params->getY2()};
	drawAxes();
    drawPoint(F1, FOCUS_RADIUS);
    drawPoint(F2, FOCUS_RADIUS);
    QPoint center = QPoint ((params->getX1() + params->getX2()) >> 1, (params->getY1() + params->getY2()) >> 1);
    drawPoint(center, FOCUS_RADIUS);
    QPoint start1 = findStart(F1 - (F2 - F1), F1);
    QPoint start2 = findStart(F2 - (F1 - F2), F2);
    drawHalf(start1, center);
    drawHalf(start2, center);
}

void Lemniscate::drawAxes() {
	uchar * pubBuffer = pBackBuffer->bits();
	int centerY = pBackBuffer->height() >> 1;
	int centerX = pBackBuffer->width() >> 1;
	int lineBytes = pBackBuffer->bytesPerLine();
	uchar green[3] = {0, 255, 0};
	for (int i = 0; i < pBackBuffer->height(); i++) {
		if (i != centerY) {
			memcpy(pubBuffer + lineBytes * i + centerX * 3, green, 3);
		}
		else {
			for (int j = 0; j < pBackBuffer->width(); j++) {
				memcpy(pubBuffer + lineBytes * i + j * 3, green, 3);
			}
		}
	}
}

void Lemniscate::drawPoint(const QPoint & point, int radius, std::array<uchar, 3> color) {
    int xcenter = width >> 1;
    int ycenter = height >> 1;
    int px = point.x() + xcenter;
    int py = ycenter - point.y();
    if (px + radius > width || py + radius > height || py - radius < 0 || px - radius < 0) {
        return;
    }
    for (int x = -radius; x < radius; x++) {
        for (int y = -radius; y < radius; y++) {
            std::copy(color.begin(), color.end(),
                      pubBuffer + 3 * (px + x)+ lineBytes * (py + y));
        }
    }
}


void Lemniscate::drawHalf(QPoint & start, QPoint & end) {
    std::vector<QPoint> firstdirs = createFirstDirections(start, end);
    for (auto & firstdir : firstdirs) {
        QPoint cur = start;
        QPoint curdir = firstdir;
        while ((cur - end).manhattanLength() > 3) {
            drawPoint(cur);
            curdir = chooseDirection(cur, curdir);
            cur += curdir;
        }
    }
}

std::vector<QPoint> Lemniscate::createFirstDirections(QPoint & start, QPoint & end) {
    QPoint perpendicular;
    perpendicular.setX(((end - start).x() > 0) - ((end - start).x() < 0));
    perpendicular.setY(((end - start).y() > 0) - ((end - start).y() < 0));
    return std::vector<QPoint> {QPoint(perpendicular.y(), - perpendicular.x()), QPoint(- perpendicular.y(), perpendicular.x())};
}

QPoint Lemniscate::chooseDirection(QPoint & curpoint, QPoint & curdir) {
    long long minerror = LLONG_MAX;
    long long direrror = LLONG_MAX;
    QPoint nextdir;
    std::vector<QPoint> directions = createDirections(curdir);
    for (auto & dir : directions) {
        direrror = llabs(error(curpoint + dir));
        if (direrror < minerror) {
            minerror = direrror;
            nextdir = dir;
        }
    }
    return nextdir;
}


std::vector<QPoint> Lemniscate::createDirections(QPoint & curdir) {
    std::vector<QPoint> directions;
    for (int x = -1; x <= 1;  x++) {
        for (int y = -1; y <= 1; y++) {
            if (y == 0 && x == 0) {
                continue;
            }
            if ((curdir - QPoint(x, y)).manhattanLength() <= 1) {
                directions.push_back(QPoint(x, y));
            }
        }
    }
    return directions;
}

long long Lemniscate::error(const QPoint &p)
{
    long long sqrR1 = (sqr(p.x() - params->getX1()) + sqr(p.y() - params->getY1()));
	long long sqrR2 = (sqr(p.x() - params->getX2()) + sqr(p.y() - params->getY2()));
	long long sqrsqrR = sqr(sqr(params->getX1() - params->getX2()) + sqr(params->getY1() - params->getY2()));
    return 16 * sqrR1 * sqrR2 - sqrsqrR;
}

long long Lemniscate::sqr(long long x) {
	return x * x;
}

QPoint Lemniscate::findStart(QPoint left, QPoint right) {
    QPoint center = left;
    long long curerror;
    while((left - right).manhattanLength() > 3) {
    	center = {(left.x() + right.x()) >> 1, (left.y() + right.y()) >> 1};
        curerror = error(center);
    	if (curerror < 0) {
    		right = center;
    	} else {
    		left = center;
    	}
    }
    return center;
}

void Lemniscate::setParams(Params * params) {
	this->params = params;
}


