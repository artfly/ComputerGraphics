#include "drawpanel.h"
#include "ui_drawpanel.h"
#include <QDebug>

DrawPanel::DrawPanel(QWidget *parent) :
	QGroupBox(PANEL_NAME, parent), ui(new Ui::DrawPanel) {
	ui->setupUi(this);
	circle = new Circle(this);
}

DrawPanel::~DrawPanel() {
	delete ui;
}

void DrawPanel::paintEvent(QPaintEvent */*event*/) {
	QPainter painter(this);
	QImage backBuffer(width(), height(), QImage::Format_RGB888);

	uchar* pubBuffer = backBuffer.bits();
	if (!pubBuffer)
	{
		return;
	}
	memset(pubBuffer, 255, backBuffer.byteCount());
	if (circle) {
		circle->draw(&backBuffer);
	}
	painter.drawImage(0,0, backBuffer);
}

void DrawPanel::redraw(Params * params) {
	circle->setParams(params);
	update();
}
