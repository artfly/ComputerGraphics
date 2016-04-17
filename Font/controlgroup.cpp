#include "controlgroup.h"
#include "ui_controlgroup.h"

ControlGroup::ControlGroup(QWidget *parent) :
    ControlInterface(parent), ui(new Ui::ControlGroup), label(new QLabel),  spinBox(new QSpinBox), slider(new QSlider(Qt::Horizontal)) {
    ui->setupUi(this);

    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

    QObject::connect(slider, SIGNAL(valueChanged(int)), parent, SLOT(setValue()));

    QGridLayout * layout = new QGridLayout;
    layout->addWidget(label, 0, 1);
    layout->addWidget(spinBox, 0, 2);
    layout->addWidget(slider, 1, 1, 1, 2);
    this->setLayout(layout);
}

ControlGroup & ControlGroup::setRange(int min, int max) {
    spinBox->setRange(min, max);
    slider->setRange(min, max);
    return * this;
}

ControlGroup & ControlGroup::setText(QString text) {
    label->setText(text);
    return * this;
}

ControlGroup::~ControlGroup()
{
    delete ui;
}
