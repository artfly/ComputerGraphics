#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QGroupBox>
#include "controlgroup.h"
#include "params.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QGroupBox
{
    Q_OBJECT

public:
	explicit ControlPanel(QWidget *parent = 0);
	void setParams(Params * params);
	Params * getParams() const;
    ~ControlPanel();
public slots:
	void setValue();
signals:
	void paramsChanged(Params * params);
private:
	static const int DEFAULT_X1 = -4;
	static const int DEFAULT_X2 = 3;
	static const int DEFAULT_Y1 = 1;
    static const int DEFAULT_Y2 = -1;
    static const int FROM_COORD = -1000;
    static const int TO = 1000;

	static constexpr const char * X1_TEXT = "Position X1";
	static constexpr const char * X2_TEXT = "Position X2";
	static constexpr const char * Y1_TEXT = "Position Y1";
	static constexpr const char * Y2_TEXT = "Position Y2";
	static constexpr const char * PANEL_NAME = "Controls";

    void createControls();
	ControlGroup * x1Controls;
	ControlGroup * y1Controls;
	ControlGroup * x2Controls;
	ControlGroup * y2Controls;

    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
