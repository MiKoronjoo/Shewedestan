#pragma once

class Node {
public:
    double xy[2]{};
    Node *left = nullptr;
    Node *right = nullptr;
    bool in_fragment = false;
    int dimension = 0;
    int state;

public:
    Node(double x, double y, int state);

    double distance(Node *that);
};
