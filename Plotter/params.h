#ifndef PARAMS_H
#define PARAMS_H
#include <QVector>

class Params {
public:
	Params(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
	int getX1() const;
	int getY1() const;
	int getX2() const;
	int getY2() const;
private:
	QVector<int> params;
};

#endif // PARAMS_H
