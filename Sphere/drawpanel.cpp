#include "drawpanel.h"
#include "ui_drawpanel.h"
#include <QDebug>

DrawPanel::DrawPanel(QWidget *parent) :
    QGroupBox(PANEL_NAME, parent), sphere(new Sphere(this)), ui(new Ui::DrawPanel) {
    ui->setupUi(this);
}

DrawPanel::~DrawPanel() {
    delete ui;
}


void DrawPanel::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar * pubBuffer = backBuffer.bits();
    if (!pubBuffer) {
        return;
    }
    memset(pubBuffer, 255, backBuffer.byteCount());
    sphere->draw(&backBuffer);
    painter.drawImage(0, 0, backBuffer);
}

void DrawPanel::redraw(Params * params) {
    sphere->setParams(params);
    update();
}


void DrawPanel::setImage(QImage & image) {
    sphere->setImage(image);
}

void DrawPanel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
       startPosition = event->pos();
    }
}

void DrawPanel::mouseMoveEvent(QMouseEvent * event) {
    if (!(event->buttons() & Qt::LeftButton))
            return;
    if ((event->pos() - startPosition).manhattanLength() < QApplication::startDragDistance())
            return;
    QPoint shift = event->pos() - startPosition;
    startPosition = event->pos();
    emit shifted(shift);
}
