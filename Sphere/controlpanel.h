#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QGroupBox>
#include "controlgroup.h"
#include "controlcombobox.h"
#include "params.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QGroupBox {
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
    void setParams(Params *params);
    Params * getParams() const;
public slots:
    void setValue();
    void shift(QPoint shift);
signals:
    void paramsChanged(Params * params);
private:
    static const int DEFAULT_COORD = 0;
    static const int DEFAULT_SCALE = 0;
    static const int MIN = -1000;
    static const int MAX = 1000;
    static constexpr const char * BILINEAR = "Bilinear";
    static constexpr const char * NEAREST = "Nearest";

    static constexpr const char * X_TEXT = "Position X";
    static constexpr const char * Y_TEXT = "Position Y";
    static constexpr const char * SCALE_TEXT = "Scale";
    static constexpr const char * FILTER = "Filter";
    static constexpr const char * PANEL_NAME = "Controls";

    void createControls();
    ControlInterface<int> * xControls;
    ControlInterface<int> * yControls;
    ControlInterface<int> * scaleControls;
    ControlInterface<QString> * filterControls;

    Ui::ControlPanel * ui;
};

#endif // CONTROLPANEL_H
