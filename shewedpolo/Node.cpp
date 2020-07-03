#include <cmath>
#include "Node.hpp"

Node::Node(double x, double y, int state) {
    xy[0] = x;
    xy[1] = y;
    this->state = state;
}

double Node::distance(Node *that) {
    return sqrt(pow(this->xy[0] - that->xy[0], 2) + pow(this->xy[1] - that->xy[1], 2));
}
