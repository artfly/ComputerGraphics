#ifndef LEMNISCATE_H
#define LEMNISCATE_H

#include <QObject>
#include <QPoint>
#include <QPair>
#include <cmath>
#include "params.h"

class Lemniscate : public QObject {
    Q_OBJECT
public:
	explicit Lemniscate(QObject *parent = 0);
signals:
public slots:
public:
	void draw(QImage* pBackBuffer);
	void setParams(Params * params);

private:
	static const int FOCUS_RADIUS = 2;

	int coord2buf(int coord, int coef, int shift);

	void drawAxes();
	QPoint drawHalf(const QPoint & center,const QPoint & restrictedDirection = QPoint(0, 0));
	QVector<QPoint> createDirections(const QPoint & restrictedDirection = QPoint(0, 0));
	long long error(const QPoint &p);
	long long sqr(int x);
	void drawPoint(const QPoint & point, int radius = 1);
	Params * params;
	QImage * pBackBuffer;
};

#endif // LEMNISCATE_H
