#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QWidget>
#include "drawpanel.h"
#include "controlpanel.h"

class Connector : public QObject
{

	Q_OBJECT

public:
	Connector();

	void attachDrawPanel(DrawPanel * panel);
	void attachControlPanel(ControlPanel * panel);
	void setX(int value);
	void setY(int value);
	void setR(int value);
	std::vector<int> getParams();
public slots:
	void setParams(std::vector<int> params);
signals:
	void paramsChanged(std::vector<int> params);
private:
	static const int DEFAULT_COORD = 0;
	static const int DEFAULT_R = 20;
	static const int FROM_R = 0;
	static const int FROM_COORD = -1000;
	static const int TO = 1000;

	QWidget * circle();
	int r;
	int x;
	int y;
};

#endif // CONNECTOR_H
