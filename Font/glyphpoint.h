#ifndef GLYPHPOINTS_H
#define GLYPHPOINTS_H

#include <QPoint>
#include "params.h"

class GlyphPoint {
public:
    GlyphPoint(int x, int y, bool oncurve) : x(x), y(y), oncurve(oncurve), params(new Params) {
        calcScale();
    }

    operator QPoint() {
        return QPoint(getX(), getY());
    }
    void changeParams(Params * params) {
        this->params = params;
        calcScale();
    }

    int getX() const {
        return  x * scale + params->getX();
    }
    int getY() const {
        return y * scale + params->getY();
    }
    bool getOncurve() const {
        return oncurve;
    }
private:
    float scale;
    int x;
    int y;
    bool oncurve;
    Params * params;

    void calcScale() {
        scale = params->getScale();
        scale = scale > 0 ? 1 + scale / 100.0 : 1 + scale / 1000.0;
    }
};

#endif // GLYPHPOINTS_H
