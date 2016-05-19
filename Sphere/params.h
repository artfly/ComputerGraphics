#ifndef PARAMS_H
#define PARAMS_H

#include <QString>

class Params {
public:
    Params(int x = 0, int y = 0,  int scale = 0,  QString filter = "Bilinear");
    int getX() const;
    int getY() const;
    int getScale() const;
    QString getFilter() const;
private:
    int x;
    int y;
    int scale;
    QString filter;
};

#endif // PARAMS_H
