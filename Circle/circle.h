#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>

class Circle : public QObject
{
    Q_OBJECT
public:
    explicit Circle(QObject *parent = 0);

signals:

public slots:
public:
    void Draw(QImage* pBackBuffer);
	void setParams(std::vector<int> params);

private:
	void drawLine(int x0, int y0, int x1, int y1, uchar * pubBuffer);
    int radius;
    int x;
    int y;
};

#endif // CIRCLE_H
