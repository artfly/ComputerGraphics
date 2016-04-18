#include "controlcheckbox.h"
#include "ui_controlcheckbox.h"

ControlCheckBox::ControlCheckBox(QWidget *parent) :
    ControlInterface(parent), ui(new Ui::ControlCheckBox), checkBox(new QCheckBox), label(new QLabel), layout(new QVBoxLayout) {
    ui->setupUi(this);

     QObject::connect(checkBox, SIGNAL(clicked(bool)), parent, SLOT(setValue()));

    layout->addWidget(checkBox);
    layout->addWidget(label);
    this->setLayout(layout);
}

ControlCheckBox & ControlCheckBox::setText(QString text) {
    label->setText(text);
    return * this;
}

ControlCheckBox::~ControlCheckBox() {
    delete ui;
}
