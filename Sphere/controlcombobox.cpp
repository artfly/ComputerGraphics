#include "controlcombobox.h"
#include "ui_controlcombobox.h"

ControlComboBox::ControlComboBox(QStringList items, QWidget * parent) :
    ControlInterface(parent), ui(new Ui::ControlComboBox), comboBox(new QComboBox), label(new QLabel), layout(new QVBoxLayout)
{
    ui->setupUi(this);
    comboBox->addItems(items);

    QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), parent, SLOT(setValue()));

    layout->addWidget(label);
    layout->addWidget(comboBox);
    this->setLayout(layout);
}

ControlComboBox & ControlComboBox::setText(QString text)
{
    label->setText(text);
    return * this;
}

ControlComboBox::~ControlComboBox()
{
    delete ui;
}
