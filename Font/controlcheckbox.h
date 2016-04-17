#ifndef CONTROLCHECKBOX_H
#define CONTROLCHECKBOX_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QLayout>
#include <controlinterface.h>

namespace Ui {
class ControlCheckBox;
}

class ControlCheckBox :  public ControlInterface<bool> {
     Q_OBJECT
 public:
    explicit ControlCheckBox(QWidget *parent = 0);
    ControlCheckBox & setText(QString text);

    ControlInterface * setValue(bool state) {
        checkBox->setChecked(state);
        return this;
    }
    bool getValue() {
        return checkBox->isChecked();
    }
    ~ControlCheckBox();

 private:
    Ui::ControlCheckBox * ui;
    QCheckBox * checkBox;
    QLabel * label;
    QLayout * layout;
};

#endif // CONTROLCHECKBOX_H
