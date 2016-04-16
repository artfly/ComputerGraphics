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
     void drawLine(int xFrom, int xTo, int y);
	Params * params;
	QImage * pBackBuffer;
    uchar * pubBuffer;
	int width;
    int height;
	int lineBytes;
};

#endif // CIRCLE_H
