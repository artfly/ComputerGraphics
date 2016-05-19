#ifndef CONTROLCOMBOBOX_H
#define CONTROLCOMBOBOX_H

#include <QComboBox>
#include <QLabel>
#include <QDebug>
#include <QLayout>
#include <QWidget>
#include <controlinterface.h>

namespace Ui {
class ControlComboBox;
}

class ControlComboBox : public ControlInterface<QString> {
    Q_OBJECT
 public:
    explicit ControlComboBox(QStringList items, QWidget * parent = 0);
    ControlComboBox & setText(QString text);
    ControlInterface * setValue(QString value) {
        int index = comboBox->findData(value);
        if (index != -1) {
            comboBox->setCurrentIndex(index);
       }
       return this;
    }

    QString getValue() {
        return comboBox->currentText();
    }
    ~ControlComboBox();

 private:
    Ui::ControlComboBox * ui;
    QComboBox * comboBox;
    QLabel * label;
    QLayout * layout;
};

#endif // CONTROLCOMBOBOX_H
