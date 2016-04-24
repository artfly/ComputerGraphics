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
    this->pBackBuffer = pBackBuffer;

    for (const auto & glyph : glyphs) {
        drawGlyph(glyph);
    }
}

void Font::drawGlyph(const std::vector<GlyphPoint *> glyph) {
    GlyphPoint * prev;
    GlyphPoint * next;
    GlyphPoint * cur;

    if (params->getOutline())
    for (size_t i = 0; i < glyph.size(); i++) {
        cur = glyph.at(i);
        drawPoint((QPoint) * cur, 2, {255, 0, 0});
        next = glyph.at((i + 1) % glyph.size());
        if (next->getOncurve() && cur->getOncurve()) {
            drawLine((QPoint) * cur, (QPoint) * next);
        } else if (!cur->getOncurve()) {
            prev = glyph.at((i - 1) % glyph.size());
            drawBezier((QPoint) * prev, (QPoint) * cur, (QPoint) * next);
        }
    }
    if (params->getFill()) {
        fill(glyph);
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
        cur = (curstart + t * curdelta) / coef;
        drawPoint(cur);
    }
}

void Font::fill(const std::vector<GlyphPoint *> glyph) {
    auto yminmax = std::minmax_element(glyph.begin(), glyph.end(),
                               [](GlyphPoint * a, GlyphPoint * b) { return a->getY() > b->getY(); });

    std::vector< std::vector<QPoint> > lines;
    GlyphPoint* prev;
    GlyphPoint * next;
    GlyphPoint * cur;
    for (size_t i = 0; i < glyph.size(); i++) {
        cur = glyph.at(i);
        next = glyph.at((i + 1) % glyph.size());
        if (next->getOncurve() && cur->getOncurve()) {
            lines.push_back( std::vector<QPoint> {(QPoint) * cur, (QPoint) * next} );
        } else if (!cur->getOncurve()) {
            prev = glyph.at((i - 1) % glyph.size());
            lines.push_back( std::vector<QPoint> {(QPoint) * prev, (QPoint) *cur, (QPoint) * next} );
        }
    }

    int x = 0;
    QPoint p1;
    QPoint p2;
    QPoint p3;
    int ycenter;
    std::vector<int> intersections;
    for (int y = (*yminmax.first)->getY(); y > (*yminmax.second)->getY(); y--) {
        intersections.clear();
       for (auto & line : lines) {
           p1 = line.at(0);
           p2 = line.at(1);
           if (line.size() == 3) {
               p3 = line.at(2);
               // center (t = 0.5)
               ycenter = 0.25 * p1.y() + 0.5 * p2.y() + 0.25 * p3.y();
               if (y <= std::max(std::max(p1.y(), ycenter), p3.y()) && y > std::min(std::min(p1.y(), ycenter), p3.y())) {
                   intersections.push_back(getBezierPointX(line, y));
               }
           } else {
               if ((p1.y() >= y && p2.y() < y) || (p1.y() < y && p2.y() >= y)) {
                   x = p1.x() + ((y - p1.y()) * (p2.x() - p1.x())) / (p2.y() - p1.y());
                   intersections.push_back(x);
               }
           }
       }
       if (intersections.size() % 2 == 0) {
           std::sort(intersections.begin(), intersections.end());
           for (size_t i = 0; i < intersections.size(); i += 2) {
               drawHorizontal(intersections.at(i), intersections.at(i + 1), y, {0, 0, 255});
           }
       }
    }
}

void Font::drawHorizontal(int xFrom, int xTo, int y, std::array<uchar, 3> color) {
    if (y < 0 || y >= pBackBuffer->height()) {
        return;
    }
    if (xFrom < 0) {
        xFrom = 0;
    }
    if (xFrom >= pBackBuffer->width()) {
        xFrom = pBackBuffer->width() - 1;
    }
    if (xTo < 0) {
        xTo = 0;
    }
    if (xTo >= pBackBuffer->width()) {
        xTo = pBackBuffer->width() - 1;
    }
    for (int x = xFrom; x < xTo; x++) {
        std::copy(color.begin(), color.end(), pubBuffer + 3 * x + lineBytes * y);
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

int Font::getBezierPointX(std::vector<QPoint> line, int y) {
    QPoint p0 = line.at(0);
    QPoint p1 = line.at(1);
    QPoint p2 = line.at(2);
    int denominator = p0.y() - 2 * p1.y() + p2.y();
    float discriminantSqrt = std::sqrt(denominator * y + sqr(p1.y()) - p0.y() * p2.y());
    float t = (p0.y() - p1.y() + discriminantSqrt) / denominator;
    if (t < 0 || t > 1) t -= 2 * discriminantSqrt / denominator;
    return (1 - t) * (1 - t) * p0.x() + 2 * t * (1 - t) * p1.x() + t * t * p2.x();
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

void Font::drawLine(QPoint from, QPoint to) {
    int x0 = from.x();
    int x1 = to.x();
    int y0 = from.y();
    int y1 = to.y();
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (params->getOutline()) {
            steep ? drawPoint(QPoint(y, x)) : drawPoint(QPoint(x, y));
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
}
