#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QGroupBox>
#include "controlsgroup.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QGroupBox
{
    Q_OBJECT

public:
	explicit ControlPanel(QWidget *parent = 0);
	void setParams(std::vector<int> params);
    ~ControlPanel();
public slots:
	void setValue();
signals:
	void paramsChanged(std::vector<int> params);
private:
    static const int DEFAULT_COORD = 0;
    static const int DEFAULT_R = 20;
    static const int FROM_R = 0;
    static const int FROM_COORD = -1000;
    static const int TO = 1000;

    static constexpr const char * X_TEXT = "Position X";
    static constexpr const char * Y_TEXT = "Position Y";
    static constexpr const char * R_TEXT = "R";
    static constexpr const char * PANEL_NAME = "Controls";

    void createControls();
    ControlsGroup * xControls;
    ControlsGroup * yControls;
    ControlsGroup * rControls;

    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
