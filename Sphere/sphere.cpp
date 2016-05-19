#include "sphere.h"
#include <math.h>
#include <functional>
#include <QDebug>

Sphere::Sphere(QObject *parent) : QObject(parent), image(new QImage()) {}

void Sphere::draw(QImage *pBackBuffer) {
   if (!params || image->isNull()) {
        return;
   }
   width = pBackBuffer->width();
   height = pBackBuffer->height();
   lineBytes = pBackBuffer->bytesPerLine();
   pubBuffer = pBackBuffer->bits();
   this->pBackBuffer = pBackBuffer;

   double scale = static_cast<double>(params->getScale());
   int r = RADIUS * (1 + scale / (scale > 0 ? 100 : 1000));

   std::pair<double, double> uv;
   QColor color;
   for (int x = -r; x <= r; x++) {
       for (int y = -r; y <= r; y++) {
           if (r * r < (x * x + y * y)) {
               continue;
           }
           uv = getTextureCoordinates({x, y}, r);
           color = getTextureColor(uv);
           drawPoint({x, y}, 1, {color.red(), color.green(), color.blue()});
       }
   }
}

std::pair<double, double> Sphere::getTextureCoordinates(std::pair<int, int> p, int r) {
    double x = p.first;
    double y = p.second;
    double z = std::sqrt(r * r - x * x - y * y);

    double theta = std::acos(y / r);
    double phi = std::atan2(z, x);

    double u = 1 - std::fmod(phi + M_PI, 2 * M_PI) / (2 * M_PI);
    double v = 1 - std::fmod(theta, M_PI) / M_PI;
    return {u, v};
}

QColor Sphere::getTextureColor(std::pair<double, double> uv) {
    if (params->getFilter() == "Nearest") {
        int x = std::round(0.5 +uv.first * image->width() + params->getX());
        int y = std::round(0.5 + uv.second * image->height() + params->getY());
        x = x % image->width() + (x > 0 ? 0 : (image->width() - 1));
        y = y % image->height() + (y > 0 ? 0 : (image->height() - 1));
        return image->pixelColor(x, y);
    } else {
        double x = std::fmod(uv.first * image->width() + params->getX(), image->width());
        double y = std::fmod(uv.second * image->height() + params->getY(), image->height());
        x = std::fmod(x + image->width(), image->width());
        y = std::fmod(y + image->height(), image->height());

        QPoint p1 = {static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y))};
        QPoint p4 = {static_cast<int>(std::ceil(x + 1)) % image->width(),
                     static_cast<int>(std::ceil(y + 1)) % image->height()};
        QPoint p2 = {p4.x(), p1.y()};
        QPoint p3 = {p1.x(), p4.y()};

        std::pair<double, double> fractionals = {x - p1.x(), y - p1.y()};

        auto channel = [](int first, int second, double fract) {
            if (first < second) std::swap(first, second);
            return static_cast<int>(first + fract * (second - first));
        };

        QVector<QColor> colors = {image->pixelColor(p1), image->pixelColor(p2),
                                  image->pixelColor(p3), image->pixelColor(p3)};

        QColor f1 = {channel(colors.at(0).red(), colors.at(2).red(), fractionals.second),
                     channel(colors.at(0).green(), colors.at(2).green(), fractionals.second),
                     channel(colors.at(0).blue(), colors.at(2).blue(), fractionals.second)};
        QColor f2 = {channel(colors.at(1).red(), colors.at(3).red(), fractionals.second),
                     channel(colors.at(1).green(), colors.at(3).green(), fractionals.second),
                     channel(colors.at(1).blue(), colors.at(3).blue(), fractionals.second)};

        return {channel(f1.red(), f2.red(), fractionals.first),
                    channel(f1.green(), f2.green(), fractionals.first),
                    channel(f1.blue(), f2.blue(), fractionals.first)};
    }
}

void Sphere::drawPoint(const QPoint & p, int r, std::array<uchar, 3> color) {
    if (std::abs(p.x()) + r >= width >> 1 || std::abs(p.y()) + r >= height >> 1)
            return;
    int centerX = pBackBuffer->width() >> 1;
    int centerY = pBackBuffer->height() >> 1;
    auto coord2buf = [] (int coordinate, int factor, int shift) {
        return coordinate * factor + shift;
    };

    for (int i = -r; i < r; i++) {
        for (int j = -r; j < r; j++) {
            std::copy(color.begin(), color.end(),
                      pubBuffer + 3 * coord2buf(p.x() + i, 1, centerX) + lineBytes * coord2buf(p.y() + j, -1, centerY));
        }
    }
}

void Sphere::setParams(Params * params) {
    this->params = params;
}

void Sphere::setImage(QImage & image) {
    this->image = new QImage(image);
}
