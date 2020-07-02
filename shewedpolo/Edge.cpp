#include "Edge.hpp"

Edge::Edge(Node *from, Node *to, double distance) : from(from), to(to), distance(distance) {}

bool Edge::operator()(const Edge e1, const Edge e2) const {
    return e1.distance > e2.distance;
}
