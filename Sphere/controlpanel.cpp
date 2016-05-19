#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QVBoxLayout>
#include <QStringList>
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

    filterControls = (new ControlComboBox(QStringList {BILINEAR, NEAREST}, this))->setText(FILTER)
            .setValue(BILINEAR);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(xControls);
    layout->addWidget(yControls);
    layout->addWidget(scaleControls);
    layout->addWidget(filterControls);
    this->setLayout(layout);
}

void ControlPanel::setValue() {
        Params * params = new Params(xControls->getValue(), yControls->getValue(),
                                     scaleControls->getValue(), filterControls->getValue());
        emit paramsChanged(params);
}

void ControlPanel::shift(QPoint shift) {
    Params * params = getParams();
    setParams(new Params(params->getX() - shift.x(), params->getY() + shift.y(), params->getScale(),
                         params->getFilter()));
}

void ControlPanel::setParams(Params * params) {
    xControls->setValue(params->getX());
    yControls->setValue(params->getY());
    scaleControls->setValue(params->getScale());
    filterControls->setValue(params->getFilter());
    emit paramsChanged(params);
}

Params * ControlPanel::getParams() const {
    Params * params = new Params(xControls->getValue(), yControls->getValue(),
                                 scaleControls->getValue(), filterControls->getValue());
    return params;
}
