#include "params.h"


Params::Params(int x, int y, int scale, bool fill, bool outline) : x(x), y(y), scale(scale), fill(fill), outline(outline) {}

int Params::getX() const {
    return x;
}

int Params::getY() const {
    return y;
}

int Params::getScale() const {
    return scale;
}

bool Params::getFill() const {
    return fill;
}

bool Params::getOutline() const {
    return outline;
}
