#include <cmath>
#include "City.hpp"


City::City(float x, float y, int state) : x(x), y(y), state(state), is_capital(false) {}

float City::distance(City &that) {
    return sqrt(pow(x - that.x, 2) + pow(y - that.y, 2));
}
