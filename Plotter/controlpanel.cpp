#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QVBoxLayout>
#include <QDebug>
#include <iostream>

ControlPanel::ControlPanel(QWidget *parent) :
	QGroupBox(PANEL_NAME, parent), ui(new Ui::ControlPanel) {
    ui->setupUi(this);
    createControls();
}

ControlPanel::~ControlPanel() {
    delete ui;
}

void ControlPanel::createControls() {
	x1Controls = new ControlGroup(this);
	y1Controls = new ControlGroup(this);
	x2Controls = new ControlGroup(this);
	y2Controls = new ControlGroup(this);

	x1Controls->setRange(FROM_COORD, TO);
	x1Controls->setText(X1_TEXT);
	x1Controls->setValue(DEFAULT_X1);

	y1Controls->setRange(FROM_COORD, TO);
	y1Controls->setText(Y1_TEXT);
	y1Controls->setValue(DEFAULT_Y1);

	x2Controls->setRange(FROM_COORD, TO);
	x2Controls->setText(X2_TEXT);
	x2Controls->setValue(DEFAULT_X2);

	y2Controls->setRange(FROM_COORD, TO);
	y2Controls->setText(Y2_TEXT);
	y2Controls->setValue(DEFAULT_Y2);

    QVBoxLayout * layout = new QVBoxLayout;
	layout->addWidget(x1Controls);
	layout->addWidget(y1Controls);
	layout->addWidget(x2Controls);
	layout->addWidget(y2Controls);
    this->setLayout(layout);
}


void ControlPanel::setValue() {
	Params * params = new Params(x1Controls->getValue(), y1Controls->getValue(),
									x2Controls->getValue(), y2Controls->getValue());
	emit paramsChanged(params);
}

void ControlPanel::setParams(Params * params) {
	x1Controls->setValue(params->getX1());
	y1Controls->setValue(params->getY1());
	x2Controls->setValue(params->getX2());
	y2Controls->setValue(params->getY2());
	emit paramsChanged(params);
}

Params * ControlPanel::getParams() const {
	Params * params = new Params(x1Controls->getValue(), y1Controls->getValue(),
									x2Controls->getValue(), y2Controls->getValue());
	return params;
}
