#include "params.h"


Params::Params(int x, int y, int r) {
	params.push_back(x);
	params.push_back(y);
	params.push_back(r);
}

int Params::getX() const {
	return params.at(0);
}

int Params::getY() const {
	return params.at(1);
}

int Params::getR() const {
	return params.at(2);
}
