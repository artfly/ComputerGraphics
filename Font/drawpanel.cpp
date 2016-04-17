#include "drawpanel.h"
#include "ui_drawpanel.h"
#include <QDebug>

DrawPanel::DrawPanel(QWidget *parent) : QGroupBox(PANEL_NAME, parent), font(new Font(this)), ui(new Ui::DrawPanel) {
    ui->setupUi(this);
}

DrawPanel::~DrawPanel() {
    delete ui;
}

void DrawPanel::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar * pubBuffer = backBuffer.bits();
    if (!pubBuffer)
    {
        return;
    }
    memset(pubBuffer, 255, backBuffer.byteCount());
    font->draw(&backBuffer);
    painter.drawImage(0,0, backBuffer);
}

void DrawPanel::redraw(Params * params) {
    font->setParams(params);
    update();
}

void DrawPanel::setGlyphs(const std::vector<std::vector<GlyphPoint *> > & glyphs) {
    font->setGlyphs(glyphs);
    update();
}
