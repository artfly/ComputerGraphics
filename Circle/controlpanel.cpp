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
	xControls = new ControlGroup(this);
    xControls->setRange(FROM_COORD, TO);
    xControls->setText(X_TEXT);
	xControls->setValue(DEFAULT_COORD);

	yControls = new ControlGroup(this);
    yControls->setRange(FROM_COORD, TO);
    yControls->setText(Y_TEXT);
	yControls->setValue(DEFAULT_COORD);

	rControls = new ControlGroup(this);
    rControls->setRange(FROM_R, TO);
    rControls->setText(R_TEXT);
	rControls->setValue(DEFAULT_R);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(xControls);
    layout->addWidget(yControls);
    layout->addWidget(rControls);
    this->setLayout(layout);
}


void ControlPanel::setValue() {
	Params * params = new Params(xControls->getValue(), yControls->getValue(), rControls->getValue());
	emit paramsChanged(params);
}

void ControlPanel::setParams(Params * params) {
	xControls->setValue(params->getX());
	yControls->setValue(params->getY());
	rControls->setValue(params->getR());
	emit paramsChanged(params);
}
