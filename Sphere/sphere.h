#ifndef SPHERE_H
#define SPHERE_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QPoint>
#include "params.h"

class Sphere : public QObject {
    Q_OBJECT
 public:
    explicit Sphere(QObject *parent = 0);
    void setImage(QImage & image);
    void setParams(Params * params);
    void draw(QImage * pBackBuffer);
 signals:

 public slots:

 private:
    static const int RADIUS = 256;
    int width;
    int height;
    int lineBytes;
    uchar * pubBuffer;
    QImage * pBackBuffer;
    QImage * image;
    Params * params;
    void drawPoint(const QPoint & p, int r = 1, std::array<uchar, 3> color = {0, 0, 0});
    QColor getTextureColor(std::pair<double, double> uv);
    std::pair<double, double> getTextureCoordinates(std::pair<int, int> p, int r);
};

#endif // SPHERE_H
