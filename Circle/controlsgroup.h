#ifndef CONTROLSGROUP_H
#define CONTROLSGROUP_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

namespace Ui {
class ControlsGroup;
}

class ControlsGroup : public QWidget
{
    Q_OBJECT

public:
    explicit ControlsGroup(QWidget *parent = 0);
    void setText(QString text);
    void setDefaultValue(int value);
    void setRange(int from, int to);
	int getValue();
	void setValue(int value);
    ~ControlsGroup();

private:
    Ui::ControlsGroup *ui;
    QLabel * label;
    QSpinBox * spinBox;
    QSlider * slider;
};

#endif // CONTROLSGROUP_H
