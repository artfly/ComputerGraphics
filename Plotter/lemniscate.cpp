#include "lemniscate.h"
#include <QImage>
#include <QDebug>
#include <cmath>
#include <climits>

Lemniscate::Lemniscate(QObject *parent) :
	QObject(parent), params(new Params()) {}

void Lemniscate::draw(QImage* pBackBuffer) {
	if (!pBackBuffer)
		return;
	this->pBackBuffer = pBackBuffer;
	QPoint F1{params->getX1(), params->getY1()};
	QPoint F2{params->getX2(), params->getY2()};
	drawAxes();
	drawPoint(F1, FOCUS_RADIUS);
	drawPoint(F2, FOCUS_RADIUS);
	QPoint center {(params->getX1() + params->getX2()) >> 1, (params->getY1() + params->getY2()) >> 1};
	drawHalf(center, drawHalf(center));
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

void Lemniscate::drawPoint(const QPoint & point, int radius) {
	uchar * pubBuffer = pBackBuffer->bits();
	uchar black[3] = {0, 0, 0};
	int width = pBackBuffer->width();
	int height = pBackBuffer->height();
	int centerX = pBackBuffer->width() >> 1;
	int centerY = pBackBuffer->height() >> 1;
	if (std::abs(point.x()) > width >> 1 || std::abs(point.y()) > height >> 1)
		return;
	for (int i = -radius; i < radius; i++) {
		for (int j = -radius; j < radius; j++) {
			memcpy(pubBuffer + coord2buf(point.y() + i, -1, centerY) * pBackBuffer->bytesPerLine() +
							   coord2buf(point.x() + j, 1, centerX) * 3, black, 3);
		}
	}
}


QPoint Lemniscate::drawHalf(const QPoint & center, const QPoint & restrictedDirection) {
	if ((abs(params->getX1() - params->getX2()) <= 3) && (abs(params->getY1() - params->getY2()) <= 3)) {
			return restrictedDirection;
	}
	int counter = 0;
	auto directions = createDirections(restrictedDirection);
	QPoint possiblePoint;
	QPoint curDirection;
	QPoint prevDirection;
	long long minError;
	bool firstPoint = true;
	QPoint curPoint = center;
	long long possibleError;
	QPoint firstDirection;

	while (true) {
		drawPoint(curPoint);
		minError = LLONG_MAX;

		for (auto & direction : directions) {
			int directionDiff = sqr(prevDirection.x() - direction.x())
					+ sqr(prevDirection.y() - direction.y());
			if (!firstPoint && directionDiff != 0 && directionDiff != 1) {
				continue;
			}
			possiblePoint = curPoint + direction;
			if (abs(possiblePoint.x() - center.x()) <= 1 && abs(possiblePoint.y() - center.y()) <= 1
					&& !firstPoint) {
				drawPoint(possiblePoint);
				return firstDirection;
			}
			possibleError = error(possiblePoint);
			if (possibleError < minError) {
				minError = possibleError;
				curDirection = direction;
			}
		}
		prevDirection = curDirection;
		if (firstPoint) {
			firstDirection = curDirection;
			firstPoint = false;
			directions = createDirections();
		}
		curPoint += curDirection;
		counter++;
		if (counter == 1000)
			return firstDirection;
	}
}


QVector<QPoint> Lemniscate::createDirections(const QPoint & restrictedDirection) {
	QVector<QPoint> directions;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1	; j++) {
			if ((i == 0 && j == 0)) {
				continue;
			}
			if (restrictedDirection != QPoint(0, 0) &&
					((restrictedDirection.x() != -i) || (restrictedDirection.y() != -j)))
				continue;

			directions.push_back(QPoint{i, j});
		}
	}
	return directions;
}

long long Lemniscate::error(const QPoint &p)
{
	long long sqrR1 = (sqr(p.x() - params->getX1()) + sqr(p.y() - params->getY1()));
	long long sqrR2 = (sqr(p.x() - params->getX2()) + sqr(p.y() - params->getY2()));
	long long sqrsqrR = sqr(sqr(params->getX1() - params->getX2()) + sqr(params->getY1() - params->getY2()));
	return llabs(16 * sqrR1 * sqrR2 - sqrsqrR);
}

long long Lemniscate::sqr(int x)
{
	return x * x;
}

void Lemniscate::setParams(Params * params) {
	this->params = params;
}

int Lemniscate::coord2buf(int coord, int coef, int shift) {
	return coord * coef + shift;
}


