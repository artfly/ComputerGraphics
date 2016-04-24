#ifndef FONT_H
#define FONT_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include <iostream>
#include <algorithm>
#include "params.h"
#include "glyphpoint.h"

class Font : public QObject {
    Q_OBJECT
public:
    explicit Font(QObject *parent = 0);
    void setGlyphs(const std::vector< std::vector<GlyphPoint *> > & glyphs);
    void setParams(Params *params);
    void draw(QImage * pBackBuffer);
signals:
public slots:
private:
    void drawGlyph(const std::vector<GlyphPoint *> glyph);
    int getBezierPointX(std::vector<QPoint> line, int y);
    void drawHorizontal(int xFrom, int xTo, int y, std::array<uchar, 3> color = {0, 0, 0});
    void drawLine(QPoint from, QPoint to);
    void fill(const std::vector<GlyphPoint *> glyph);
    void drawBezier(QPoint start, QPoint control, QPoint end);
    void drawPoint(const QPoint & p, int r = 1, std::array<uchar, 3> color = {0, 0, 0});
    int sqr(int a);
    QPoint qabs(const QPoint & point);
    int width;
    int height;
    int lineBytes;
    uchar * pubBuffer;
    QImage * pBackBuffer;
    GlyphPoint * maxleft;
    GlyphPoint * maxright;
    GlyphPoint * maxtop;
    GlyphPoint * maxbottom;
    std::vector< std::vector<GlyphPoint *> > glyphs;
    std::vector<QPoint> bezierPoints;
    Params * params;
};

#endif // FONT_H
