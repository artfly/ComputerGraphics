#ifndef FONT_H
#define FONT_H

#include <QObject>
#include <QImage>
#include <QPoint>
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
//    void drawLine(QPoint from, QPoint to);
    void drawBezier(QPoint start, QPoint control, QPoint end);
    void drawPoint(const QPoint & p, int r = 1, std::array<uchar, 3> color = {0, 0, 0});
    int sqr(int a);
    QPoint qabs(const QPoint & point);
    int width;
    int height;
    int lineBytes;
    uchar * pubBuffer;
   std::vector< std::vector<GlyphPoint *> > glyphs;
   Params * params;
};

#endif // FONT_H
