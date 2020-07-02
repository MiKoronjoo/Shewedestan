#pragma once

#include "Node.hpp"

class Edge {
public:
    Node *from = nullptr;
    Node *to = nullptr;
    double distance = 0;

public:
    Edge(Node *from, Node *to, double distance);

    bool operator()(Edge e1, Edge e2) const;
};
