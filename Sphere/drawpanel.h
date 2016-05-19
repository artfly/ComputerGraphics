#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QString>
#include <QMouseEvent>
#include "params.h"
#include "sphere.h"

namespace Ui {
class DrawPanel;
}

class DrawPanel : public QGroupBox {
    Q_OBJECT
public:
    explicit DrawPanel(QWidget *parent = 0);
    void setImage(QImage & image);
    ~DrawPanel();
signals:
    void shifted(QPoint shift);
public slots:
    void redraw(Params * params);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
private:
    static constexpr const char * PANEL_NAME = "Draw Panel";
    QPoint startPosition;
    Sphere * sphere;
    Ui::DrawPanel * ui;
};

#endif // DRAWPANEL_H
