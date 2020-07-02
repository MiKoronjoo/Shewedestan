#pragma once

class Node {
public:
    double xy[2]{};
    Node *left = nullptr;
    Node *right = nullptr;
    bool in_fragment = false;
    int dimension = 0;

public:
    Node(double x, double y);

    double distance(Node *that);
};
