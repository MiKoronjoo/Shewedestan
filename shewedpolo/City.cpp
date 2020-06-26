#include <cmath>
#include "City.hpp"


City::City(float x, float y, int state) : x(x), y(y), max_dis(0), state(state), is_capital(false) {}

float City::distance(City *that) {
    return sqrt(pow(x - that->x, 2) + pow(y - that->y, 2));
}

float City::distance(float x0, float y0) const {
    return sqrt(pow(x - x0, 2) + pow(y - y0, 2));
}

float City::getX() const {
    return x;
}

float City::getY() const {
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

float City::getMaxDis() const {
    return max_dis;
}

void City::setMaxDis(float maxDis) {
    max_dis = maxDis;
}
