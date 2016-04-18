#include "font.h"
#include <QDebug>

Font::Font(QObject *parent) : QObject(parent) {}

void Font::draw(QImage * pBackBuffer) {
    if (!pBackBuffer || !params || glyphs.empty()) {
        return;
    }
    width = pBackBuffer->width();
    height = pBackBuffer->height();
    lineBytes = pBackBuffer->bytesPerLine();
    pubBuffer = pBackBuffer->bits();

    for (const auto & glyph : glyphs) {
        drawGlyph(glyph);
    }
}

void Font::drawGlyph(const std::vector<GlyphPoint *> glyph) {
    GlyphPoint * prev;
    GlyphPoint * next;
    GlyphPoint * cur;
    QPoint center;

    for (size_t i = 0; i < glyph.size(); i++) {
        cur = glyph.at(i);
        drawPoint((QPoint) * cur, 2, {255, 0, 0});
        next = glyph.at((i + 1) % glyph.size());
        if (next->getOncurve() && cur->getOncurve()) {
            center.setX((cur->getX() + next->getX()) >> 1);
            center.setY((cur->getY() + next->getY()) >> 1);
            drawBezier((QPoint) * cur, center, (QPoint) * next);
        } else if (!cur->getOncurve()) {
            prev = glyph.at((i - 1) % glyph.size());
            drawBezier((QPoint) * prev, (QPoint) * cur, (QPoint) * next);
        }
    }
}

void Font::drawBezier (QPoint start, QPoint control, QPoint end) {
    int d1 = std::sqrt(sqr(start.x() - control.x()) + sqr(start.y() - control.y()));
    int d2 = std::sqrt(sqr(end.x() - control.x()) + sqr(end.y() - control.y()));
    int coef = (d1 >= d2) * d1 + (d1 < d2) * d2;

    QPoint deltastart = (start - control);
    QPoint deltaend = (control - end);
    QPoint curstart =coef * start;
    QPoint curend = coef * control;
    QPoint curdelta;
    QPoint cur;
    for (int t =0; t <= coef; t++) {
        curstart -= deltastart;
        curend -= deltaend;
        curdelta = (curend - curstart) / coef;
        cur = curstart + t * curdelta;
        if (params->getOutline()) {
            drawPoint(cur / coef);
        }
    }
}

void Font::setParams(Params * params) {
    this->params = params;
    for (const auto & glyph : glyphs) {
        for (const auto & point : glyph) {
            point->changeParams(params);
        }
    }
}

int Font::sqr(int a) {
    return a * a;
}

QPoint Font::qabs(const QPoint & point) {
    return QPoint(std::abs(point.x()), std::abs(point.y()));
}

void Font::setGlyphs(const std::vector<std::vector<GlyphPoint *> > & glyphs) {
    this->glyphs = glyphs;
}

void Font::drawPoint(const QPoint & p, int r, std::array<uchar, 3> color) {
    if (p.x() - r < 0 || p.x() + r >= width || p.y() - r < 0 || p.y() + r > height) {
        return;
    }
    for (int i = -r; i < r; i++) {
        for (int j = -r; j < r; j++) {
            std::copy(color.begin(), color.end(), pubBuffer + 3 * (p.x() + i) + lineBytes * (p.y() + j));
        }
    }
}

//void Font::drawLine(QPoint from, QPoint to) {
//    drawPoint(from, to, 3, {0, 0, 255});
//    drawPoint(xTo, yTo, 3, {255, 0, 0});
//    int xDiff = std::abs(xTo - from);
//    int yDiff = std::abs(yTo - to);
//    int error = 0;
//    int errorDiff = yDiff;
//    int from = xTo < from ? xTo : from;
//    int to = from == xTo ? from : xTo;
//    int y = from == from ? to : yTo;
//    for (int x = from; x <= to; x++) {
//        drawPoint(x, y);
//        error += errorDiff;
//        if (error << 1 >= xDiff) {
//            y--;
//            error -= errorDiff;
//        }
//    }
//}
