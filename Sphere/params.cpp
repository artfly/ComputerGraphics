#include "params.h"


Params::Params(int x, int y, int scale, QString filter) : x(x), y(y), scale(scale), filter(filter) {}

int Params::getX() const {
    return x;
}

int Params::getY() const {
    return y;
}

int Params::getScale() const {
    return scale;
}

QString Params::getFilter() const
{
    return filter;
}
