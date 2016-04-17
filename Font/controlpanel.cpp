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
    xControls = (new ControlGroup(this))->setRange(MIN, MAX)
            .setText(X_TEXT)
            .setValue(DEFAULT_COORD);
    yControls = (new ControlGroup(this))->setRange(MIN, MAX)
            .setText(Y_TEXT)
            .setValue(DEFAULT_COORD);

    scaleControls = (new ControlGroup(this))->setRange(MIN, MAX)
            .setText(SCALE_TEXT)
            .setValue(DEFAULT_SCALE);

    fillControls = (new ControlCheckBox(this))->setText(FILL_TEXT)
            .setValue(DEFAULT_FILL);

   outlineControls = (new ControlCheckBox(this))->setText(OUTLINE_TEXT)
           .setValue(DEFAULT_OUTLINE);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(xControls);
    layout->addWidget(yControls);
    layout->addWidget(scaleControls);
    QHBoxLayout * hLayout = new QHBoxLayout();
    hLayout->addWidget(fillControls);
    hLayout->addWidget(outlineControls);
    layout->addLayout(hLayout);
    this->setLayout(layout);
}


void ControlPanel::setValue() {
        Params * params = new Params(xControls->getValue(), yControls->getValue(),
                                     scaleControls->getValue(), fillControls->getValue(), outlineControls->getValue());
        emit paramsChanged(params);
}

void ControlPanel::setParams(Params * params) {
    xControls->setValue(params->getX());
    yControls->setValue(params->getY());
    scaleControls->setValue(params->getScale());
    fillControls->setValue(params->getFill());
    outlineControls->setValue(params->getOutline());
    emit paramsChanged(params);
}

Params * ControlPanel::getParams() const {
    Params * params = new Params(xControls->getValue(), yControls->getValue(),
                                 scaleControls->getValue(), fillControls->getValue(), outlineControls->getValue());
    return params;
}
