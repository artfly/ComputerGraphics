#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QVBoxLayout>
#include <QDebug>
#include <iostream>

ControlPanel::ControlPanel(QWidget *parent) :
	QGroupBox(PANEL_NAME, parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    createControls();
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::createControls() {
	xControls = new ControlsGroup(this);
    xControls->setRange(FROM_COORD, TO);
    xControls->setText(X_TEXT);
    xControls->setDefaultValue(DEFAULT_COORD);

	yControls = new ControlsGroup(this);
    yControls->setRange(FROM_COORD, TO);
    yControls->setText(Y_TEXT);
    yControls->setDefaultValue(DEFAULT_COORD);

	rControls = new ControlsGroup(this);
    rControls->setRange(FROM_R, TO);
    rControls->setText(R_TEXT);
    rControls->setDefaultValue(DEFAULT_R);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(xControls);
    layout->addWidget(yControls);
    layout->addWidget(rControls);
    this->setLayout(layout);
}


void ControlPanel::setValue() {
	std::vector<int> params;
	params.push_back(xControls->getValue());
	params.push_back(yControls->getValue());
	params.push_back(rControls->getValue());
	emit paramsChanged(params);
}

void ControlPanel::setParams(std::vector<int> params) {
	xControls->setValue(params[0]);
	yControls->setValue(params[1]);
	rControls->setValue(params[2]);
	emit paramsChanged(params);
}
