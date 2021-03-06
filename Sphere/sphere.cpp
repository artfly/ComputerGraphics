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
   double y;

   std::pair<double, double> uv;
   QColor color = {0, 0, 0};

   for (int x = 0; x < width; x++) {
       for (int z = r; z <= height - r; z++) {
           if (std::abs(2 * x - width) > 2 * r) {
               continue;
           }
           y = z - std::sqrt(r * r - (x - width / 2) * (x - width / 2));
           uv = getTextureCoordinates({x, y}, r);
           color = getTextureColor(uv);
           drawPoint({width - x, height - y}, {color.red(), color.green(), color.blue()});
       }
   }

   for (int x = 0; x < width; x++) {
       for (int y = 0; y < height; y++) {
           if (4 * r * r < (2 * x - width) * (2 * x - width) + 4 * (y - r) * (y - r)) {
               continue;
           }
           uv = getTextureCoordinates({x, height - y}, r);
           color = getTextureColor(uv);
           drawPoint({width - x, y}, {color.red(), color.green(), color.blue()});
       }
   }
}

std::pair<double, double> Sphere::getTextureCoordinates(std::pair<double, double> p, int r) {
    double x = p.first;
    double y = std::sqrt(4 * r * r - (2 * x - width) * (2 * x - width));

    double phi = std::atan2(2 * y, 2 * x - width);

    double u = 1 - p.second / height;
    double v = 1 - (2 * phi + M_PI) / (2 * M_PI);
    return {v, u};
}

QColor Sphere::getTextureColor(std::pair<double, double> uv) {
    if (params->getFilter() == "Nearest") {
        int x = std::round(0.5 + uv.first * image->width() + params->getX());
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
        QPoint p4 = {static_cast<int>(std::ceil(x)) % image->width(),
                     static_cast<int>(std::ceil(y)) % image->height()};
        QPoint p2 = {p4.x(), p1.y()};
        QPoint p3 = {p1.x(), p4.y()};

        std::pair<double, double> fractionals = {x - p1.x(), y - p1.y()};

        auto channel = [](int first, int second, double fract) {
            return static_cast<int>(first + fract * (second - first));
        };
        QVector<QColor> colors = {image->pixelColor(p1), image->pixelColor(p2),
                                  image->pixelColor(p3), image->pixelColor(p4)};

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

void Sphere::drawPoint(const QPoint & p, std::array<int, 3> color) {
    std::copy(color.begin(), color.end(), pubBuffer + 3 * p.x() + lineBytes * p.y());
}

void Sphere::setParams(Params * params) {
    this->params = params;
}

void Sphere::setImage(QImage & image) {
    this->image = new QImage(image);
}

