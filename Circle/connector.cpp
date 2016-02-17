#include "connector.h"
#include <iostream>

Connector::Connector() {
	x = DEFAULT_COORD;
	y = DEFAULT_COORD;
	r = DEFAULT_COORD;
}

void Connector::attachControlPanel(ControlPanel * panel) {
	QObject::connect(panel, SIGNAL(paramsChanged(std::vector<int>)),
						this, SLOT(setParams(std::vector<int>)));
}

void Connector::attachDrawPanel(DrawPanel * panel) {
	QObject::connect(this, SIGNAL(paramsChanged(std::vector<int>)),
					 panel, SLOT(redraw(std::vector<int>)));
}

void Connector::setParams(std::vector<int> params) {
	emit paramsChanged(params);
}

//void Connector::setX(int value) {
//	x = value;
//	emit paramsChanged(getParams());
//}

//void Connector::setY(int value) {
//	y = value;
//	emit paramsChanged(getParams());
//}

//void Connector::setR(int value) {
//	r = value;
//	emit paramsChanged(getParams());
//}

//void Connector::setParams(std::vector<int> params) {
//	emitParamsChanged(params);
//}
