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
    static const int FOCUS_RADIUS = 5;

	int coord2buf(int coord, int coef, int shift);
    void drawHalf(QPoint & start, QPoint & end);
    std::vector<QPoint> createDirections(QPoint & curdir);
    std::vector<QPoint> createFirstDirections(QPoint & start, QPoint & end);
    QPoint chooseDirection(QPoint & curpoint, QPoint & curdir);
    QPoint findStart(QPoint left, QPoint right);
    void drawAxes();
	long long error(const QPoint &p);
    long long sqr(long long x);
    void drawPoint(const QPoint & p, int r = 1, std::array<uchar, 3> color = {0, 0, 0});
	Params * params;
    int width;
    int height;
    int lineBytes;
    uchar * pubBuffer;
    QImage * pBackBuffer;
};

#endif // LEMNISCATE_H
