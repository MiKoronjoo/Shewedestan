#include "KDTree.hpp"

KDTree::KDTree(int k) : k(k) {}

Node *KDTree::make() {
    double x, y;
    int state, count;
    std::cin >> count;
    edges = count - 1;
    std::cin >> x >> y >> state;
    Node *first_node = new Node(x, y, state);
    for (int i = 0; i < edges; ++i) {
        std::cin >> x >> y >> state;
        Node *new_node = new Node(x, y, state);
        this->insert(this->root, new_node, 0);
    }
    return first_node;
}

Node *KDTree::make(std::vector<Node *> &nodes) {
    edges = nodes.size() - 1;
    Node *first_node = nodes[0];
    for (int i = 1; i < nodes.size(); ++i) {
        this->insert(this->root, nodes[i], 0);
    }
    return first_node;
}

void KDTree::search_nearest(Node *this_node, Node *that_node) {
    double distance = this_node->distance(that_node);
    int this_d = this_node->dimension;
    if (not nearest_node or distance < best_distance) {
        nearest_node = this_node;
        best_distance = distance;
    }
    if (that_node->xy[this_d] < this_node->xy[this_d]) {
        if (this_node->left)
            search_nearest(this_node->left, that_node);
    } else if (this_node->right) {
        search_nearest(this_node->right, that_node);
    }

    double temp = std::abs(this_node->xy[this_d] - that_node->xy[this_d]);
    if (temp < best_distance) {
        if (that_node->xy[this_d] < this_node->xy[this_d]) {
            if (this_node->right)
                search_nearest(this_node->right, that_node);
        } else {
            if (this_node->left)
                search_nearest(this_node->left, that_node);
        }
    }
}

pnn KDTree::search_dimension(Node *this_node, Node *parent, int that_dimension) {
    if (this_node->dimension == that_dimension) {
        if (not this_node->left)
            return {parent, this_node};
        return search_dimension(this_node->left, this_node, that_dimension);
    }
    pnn right_min = {nullptr, nullptr};
    pnn left_min = {nullptr, nullptr};
    if (this_node->right)
        right_min = search_dimension(this_node->right, this_node, that_dimension);

    if (this_node->left)
        left_min = search_dimension(this_node->left, this_node, that_dimension);

    if (not right_min.second and left_min.second) {
        if (left_min.second->xy[that_dimension] < this_node->xy[that_dimension])
            return left_min;
        return {parent, this_node};
    } else if (not left_min.second and right_min.second) {
        if (right_min.second->xy[that_dimension] < this_node->xy[that_dimension])
            return right_min;
        return {parent, this_node};

    } else if (not right_min.second and not left_min.second) {
        return {parent, this_node};
    } else {
        if (left_min.second->xy[that_dimension] <= right_min.second->xy[that_dimension]) {
            if (left_min.second->xy[that_dimension] < this_node->xy[that_dimension])
                return left_min;
            return {parent, this_node};
        } else {
            if (right_min.second->xy[that_dimension] < this_node->xy[that_dimension])
                return right_min;
            return {parent, this_node};
        }
    }
}

void KDTree::insert(Node *this_node, Node *that_node, int depth) {
    int dimension = depth % k;
    if (not root) {
        root = that_node;
        that_node->dimension = dimension;
        return;
    }
    if (that_node->xy[dimension] < this_node->xy[dimension]) {
        if (not this_node->left) {
            this_node->left = that_node;
            that_node->dimension = (depth + 1) % k;
            return;
        } else {
            return insert(this_node->left, that_node, depth + 1);
        }
    } else {
        if (not this_node->right) {
            this_node->right = that_node;
            that_node->dimension = (depth + 1) % k;
            return;
        } else {
            return insert(this_node->right, that_node, depth + 1);
        }
    }
}

void KDTree::delete_node(Node *this_node, Node *parent, Node *that_node) {
    if (this_node == that_node) {
        if (this_node->right) {
            pnn min = search_dimension(this_node->right, this_node, this_node->dimension);

            delete_node(min.second, min.first, min.second);

            min.second->dimension = this_node->dimension;
            min.second->right = this_node->right;
            min.second->left = this_node->left;
            if (not parent) {
                root = min.second;
            } else {
                if (parent->left == this_node) {
                    parent->left = min.second;
                } else if (parent->right == this_node) {
                    parent->right = min.second;
                }
            }
        } else if (this_node->left) {
            pnn min = search_dimension(this_node->left, this_node, this_node->dimension);

            delete_node(min.second, min.first, min.second);

            min.second->dimension = this_node->dimension;
            min.second->right = this_node->left;
            min.second->left = nullptr;
            if (not parent) {
                root = min.second;
            } else {
                if (parent->left == this_node) {
                    parent->left = min.second;
                } else if (parent->right == this_node) {
                    parent->right = min.second;
                }
            }
        } else if (parent) {
            if (parent->left == this_node) {
                parent->left = nullptr;
            } else if (parent->right == this_node) {
                parent->right = nullptr;
            }
        }
    } else {
        if (that_node->xy[this_node->dimension] < this_node->xy[this_node->dimension])
            delete_node(this_node->left, this_node, that_node);
        else
            delete_node(this_node->right, this_node, that_node);
    }
}
