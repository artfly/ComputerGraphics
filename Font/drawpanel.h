#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QString>
#include "params.h"
#include "font.h"

namespace Ui {
class DrawPanel;
}

class DrawPanel : public QGroupBox {
    Q_OBJECT
public:
    explicit DrawPanel(QWidget *parent = 0);
    void setGlyphs(const std::vector<std::vector<GlyphPoint *> > & glyphs);
    ~DrawPanel();
signals:

public slots:
    void redraw(Params * params);
protected:
    void paintEvent(QPaintEvent *event);
private:
    static constexpr const char * PANEL_NAME = "Draw Panel";

    Font * font;
    Ui::DrawPanel * ui;
};

#endif // DRAWPANEL_H
