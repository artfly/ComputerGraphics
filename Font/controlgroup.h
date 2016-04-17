#ifndef ControlGroup_H
#define ControlGroup_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QGridLayout>
#include <controlinterface.h>

namespace Ui {
class ControlGroup;
}

class ControlGroup : public ControlInterface<int> {
    Q_OBJECT

public:
    explicit ControlGroup(QWidget *parent = 0);
    ControlGroup & setText(QString text);
    ControlGroup & setRange(int min, int max);

    ControlInterface * setValue(int value) {
        slider->setValue(value);
        spinBox->setValue(value);
        return this;
    }
    int getValue() {
        return slider->value();
    }

    ~ControlGroup();

private:
    Ui::ControlGroup *ui;
    QLabel * label;
    QSpinBox * spinBox;
    QSlider * slider;
    QGridLayout * layout;
};

#endif // ControlGroup_H
