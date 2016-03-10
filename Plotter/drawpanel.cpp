#include "drawpanel.h"
#include "ui_drawpanel.h"
#include <QDebug>

DrawPanel::DrawPanel(QWidget *parent) :
	QGroupBox(PANEL_NAME, parent), ui(new Ui::DrawPanel) {
	ui->setupUi(this);
	lemniscate = new Lemniscate(this);
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
	if (lemniscate) {
		lemniscate->draw(&backBuffer);
	}
	painter.drawImage(0,0, backBuffer);
}

void DrawPanel::redraw(Params * params) {
	lemniscate->setParams(params);
	update();
}
