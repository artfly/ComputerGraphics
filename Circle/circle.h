#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QPair>
#include "params.h"

class Circle : public QObject {
    Q_OBJECT
public:
    explicit Circle(QObject *parent = 0);
signals:
public slots:
public:
	void draw(QImage* pBackBuffer);
	void setParams(Params * params);

private:
	QPair<int, int> buf2pair(int point);
	int findIntersection(int border);
	Params * params;
	int width;
	int height;
	int x0;
	int y0;
	int r;
	int lineBytes;
};

#endif // CIRCLE_H
