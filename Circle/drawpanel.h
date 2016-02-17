#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QString>
#include "circle.h"
#include "params.h"

namespace Ui {
class DrawPanel;
}

class DrawPanel : public QGroupBox {
	Q_OBJECT

public:
	explicit DrawPanel(QWidget *parent = 0);
	~DrawPanel();
signals:

public slots:
	void redraw(Params * params);
protected:
	void paintEvent(QPaintEvent *event);

private:
	static constexpr const char * PANEL_NAME = "Draw Panel";
	Circle * circle;
	Ui::DrawPanel * ui;

};

#endif // DRAWPANEL_H
