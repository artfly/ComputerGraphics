#include "controlgroup.h"
#include "ui_controlgroup.h"
#include <QGridLayout>

ControlGroup::ControlGroup(QWidget *parent) :
	QWidget(parent), ui(new Ui::ControlGroup) {
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

void ControlGroup::setRange(int from, int to) {
    spinBox->setRange(from, to);
    slider->setRange(from, to);
}

void ControlGroup::setText(QString text) {
    label->setText(text);
}

int ControlGroup::getValue() {
	return slider->value();
}

ControlGroup::~ControlGroup()
{
    delete ui;
}

void ControlGroup::setValue(int value) {
	spinBox->setValue(value);
	slider->setValue(value);
}
