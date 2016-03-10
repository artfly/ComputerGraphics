#ifndef ControlGroup_H
#define ControlGroup_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

namespace Ui {
class ControlGroup;
}

class ControlGroup : public QWidget {
    Q_OBJECT

public:
    explicit ControlGroup(QWidget *parent = 0);
    void setText(QString text);
    void setRange(int from, int to);
	int getValue();
	void setValue(int value);
    ~ControlGroup();

private:
    Ui::ControlGroup *ui;
    QLabel * label;
    QSpinBox * spinBox;
    QSlider * slider;
};

#endif // ControlGroup_H
