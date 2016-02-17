#ifndef PARAMS_H
#define PARAMS_H
#include <QVector>

class Params {
public:
	Params(int x = 0, int y = 0, int r = 20);
	int getX() const;
	int getY() const;
	int getR() const;
private:
	QVector<int> params;
};

#endif // PARAMS_H
