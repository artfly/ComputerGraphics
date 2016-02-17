#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
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
	Params * params;
};

#endif // CIRCLE_H
