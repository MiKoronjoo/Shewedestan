#include <cmath>
#include "City.hpp"


City::City(double x, double y, int state) : x(x), y(y), max_dis(0), state(state), is_capital(false) {}

double City::distance(City *that) {
    return sqrt(pow(x - that->x, 2) + pow(y - that->y, 2));
}

double City::distance(double x0, double y0) const {
    return sqrt(pow(x - x0, 2) + pow(y - y0, 2));
}

double City::getX() const {
    return x;
}

double City::getY() const {
    return y;
}

int City::getState() const {
    return state;
}

bool City::isCapital() const {
    return is_capital;
}

void City::setIsCapital(bool isCapital) {
    is_capital = isCapital;
}

double City::getMaxDis() const {
    return max_dis;
}

void City::setMaxDis(double maxDis) {
    max_dis = maxDis;
}
