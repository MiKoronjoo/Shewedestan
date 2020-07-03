#pragma once

#include<cmath>
#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"

using pnn = std::pair<Node *, Node *>;

class KDTree {
public:
    int edges{};
    int k;
    Node *root = nullptr;
    Node *nearest_node = nullptr;
    double best_distance{};

public:
    explicit KDTree(int k);

    Node *make();

    void search_nearest(Node *this_node, Node *that_node);

    static pnn search_dimension(Node *this_node, Node *parent, int that_dimension);

    void insert(Node *this_node, Node *that_node, int depth);

    void delete_node(Node *this_node, Node *parent, Node *that_node);
};
