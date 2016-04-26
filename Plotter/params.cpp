#include "params.h"
#include <iostream>

Params::Params(int x1, int y1, int x2, int y2) {
    params.push_back(x1);
    params.push_back(y1);
    params.push_back(x2);
    params.push_back(y2);
}

int Params::getX1() const {
	return params.at(0);
}

int Params::getY1() const {
	return params.at(1);
}

int Params::getX2() const {
	return params.at(2);
}

int Params::getY2() const {
	return params.at(3);
}
