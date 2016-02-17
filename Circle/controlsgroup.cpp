#include "controlsgroup.h"
#include "ui_controlsgroup.h"
#include <QGridLayout>

ControlsGroup::ControlsGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlsGroup)
{
    ui->setupUi(this);

    label = new QLabel();
    spinBox = new QSpinBox();
    slider = new QSlider(Qt::Horizontal);
	QObject::connect(spinBox, SIGNAL(valueChanged(int)),slider, SLOT(setValue(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)),spinBox, SLOT(setValue(int)));

	QObject::connect(slider, SIGNAL(valueChanged(int)), parent, SLOT(setValue()));

    QGridLayout * layout = new QGridLayout;
    layout->addWidget(label, 0, 1);
    layout->addWidget(spinBox, 0, 2);
    layout->addWidget(slider, 1, 1, 1, 2);
    this->setLayout(layout);
}

void ControlsGroup::setDefaultValue(int value) {
    spinBox->setValue(value);
    slider->setValue(value);
}

void ControlsGroup::setRange(int from, int to) {
    spinBox->setRange(from, to);
    slider->setRange(from, to);
}

void ControlsGroup::setText(QString text) {
    label->setText(text);
}

int ControlsGroup::getValue() {
	return slider->value();
}

ControlsGroup::~ControlsGroup()
{
    delete ui;
}

void ControlsGroup::setValue(int value) {
	spinBox->setValue(value);
	slider->setValue(value);
}
