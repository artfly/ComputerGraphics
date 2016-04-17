#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include <QWidget>

template <class T>
class ControlInterface : public QWidget {
public:
    ControlInterface(QWidget * parent) : QWidget(parent) {}
    virtual T getValue() = 0;
    virtual ControlInterface * setValue(T value) = 0;
};

#endif // CONTROLINTERFACE_H
