#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "shewedpolo/KDTree.hpp"
#include "shewedpolo/City.hpp"
#include "shewedpolo/Path.hpp"

#define INF MAXFLOAT

double prim(std::vector<City *> &cities) {
    double total_weight = 0;
    int n = cities.size();
    std::vector<bool> selected(n, false);
    std::vector<Path> min_e(n);
    min_e[0].distance = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (not selected[j] and (v == -1 or min_e[j].distance < min_e[v].distance))
                v = j;
        }
        if (min_e[v].distance == INF) {
            std::cout << "No MST!" << std::endl;
            return 0;
        }
        selected[v] = true;
        total_weight += min_e[v].distance;
//        if (min_e[v].to != -1)
//            std::cout << v + 1 << " " << min_e[v].to + 1 << std::endl;
        for (int to = 0; to < n; ++to) {
            if (cities[v]->distance(cities[to]) < min_e[to].distance)
                min_e[to] = {cities[v]->distance(cities[to]), v};
        }
    }
    return total_weight;
}

double state_prim(std::vector<std::vector<City *>> &states) {
    double total_weight = 0;
    int n = states.size();
    std::vector<bool> selected(n, false);
    std::vector<Path> min_e(n);
    min_e[0].distance = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (not selected[j] and (v == -1 or min_e[j].distance < min_e[v].distance))
                v = j;
        }
        if (min_e[v].distance == INF) {
            std::cout << "No MST!" << std::endl;
            return 0;
        }
        selected[v] = true;
        total_weight += min_e[v].distance;
        int this_state = states[v].size();
        for (int ts = 0; ts < this_state; ++ts)
            for (int to = 0; to < n; ++to) {
                int ct = states[to].size();
                for (int t = 0; t < ct; ++t)
                    if (states[v][ts]->distance(states[to][t]) < min_e[to].distance)
                        min_e[to] = {states[v][ts]->distance(states[to][t]), v};
            }
    }
    return total_weight;
}

double sep_prim(std::vector<City *> &cities) {
    int n = cities[cities.size() - 1]->getState();
    std::vector<std::vector<City *>> states(n);
    for (auto &city: cities) {
        states[city->getState() - 1].push_back(city);
    }
    double total_weight = 0;
    for (auto state: states) {
        if (state.empty())
            continue;
        total_weight += prim(state);
    }
    total_weight += state_prim(states);
    return total_weight;
}

void find_capitals(std::vector<City *> &cities) {
    int n = cities.size();
    std::vector<std::vector<int>> indexes(n);
    for (int i = 0; i < n; i++) {
        indexes[cities[i]->getState() - 1].push_back(i);
    }
    for (const auto &state: indexes) {
        if (state.empty())
            continue;
        for (int i: state) {
            for (int j: state) {
                double dis = cities[i]->distance(cities[j]);
                if (dis > cities[i]->getMaxDis()) {
                    cities[i]->setMaxDis(dis);
                }
            }
        }
        double min_dis = INF;
        int cap_indx = -1;
        for (int i: state) {
            if (cities[i]->getMaxDis() < min_dis) {
                min_dis = cities[i]->getMaxDis();
                cap_indx = i;
            }
        }
        cities[cap_indx]->setIsCapital(true);
        std::cout << cities[cap_indx]->getState() << ": " << cap_indx + 1 << std::endl;
    }
}

bool compare(const Edge &e1, const Edge &e2) {
    return e1.distance >= e2.distance;
}

void phase1a() {
    int count, state;
    double x, y;
    std::cin >> count;
    std::vector<City *> cities;
    cities.reserve(count);
    for (int i = 0; i < count; i++) {
        std::cin >> x >> y >> state;
        cities.push_back(new City(x, y, state));
    }
    double total_weight = prim(cities);
    printf("%.2f\n", total_weight);
}

void phase1b() {
    double total_weight = 0;
    auto kdtree = new KDTree(2);
    std::vector<Edge> edges;
    std::vector<Edge> MST;

    Node *first_node = kdtree->make();
    first_node->in_fragment = true;

    kdtree->search_nearest(kdtree->root, first_node);

    edges.emplace_back(first_node, kdtree->nearest_node, kdtree->best_distance);
    make_heap(edges.begin(), edges.end(), &compare);

    while (kdtree->edges != MST.size()) {
        Edge &candidate_edge = edges.front();

        if (not candidate_edge.to->in_fragment) {
            Node *new_node_in_fragment = candidate_edge.to;
            new_node_in_fragment->in_fragment = true;
            MST.push_back(candidate_edge);
            total_weight += candidate_edge.distance;

            kdtree->delete_node(kdtree->root, nullptr, new_node_in_fragment);

            kdtree->nearest_node = nullptr;
            kdtree->search_nearest(kdtree->root, new_node_in_fragment);

            edges.emplace_back(new_node_in_fragment, kdtree->nearest_node, kdtree->best_distance);
            push_heap(edges.begin(), edges.end(), &compare);

        } else {
            Node *source_node = candidate_edge.from;

            pop_heap(edges.begin(), edges.end(), &compare);
            edges.pop_back();

            kdtree->nearest_node = nullptr;
            kdtree->search_nearest(kdtree->root, source_node);
            edges.emplace_back(source_node, kdtree->nearest_node, kdtree->best_distance);
            push_heap(edges.begin(), edges.end(), &compare);
        }
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << total_weight << std::endl;
}

void phase1c() {
    int count, state;
    double x, y;
    std::cin >> count;
    std::vector<City *> cities;
    cities.reserve(count);
    for (int i = 0; i < count; i++) {
        std::cin >> x >> y >> state;
        cities.push_back(new City(x, y, state));
    }
    find_capitals(cities);
}

void phase2a() {
    int count, state;
    double x, y;
    std::cin >> count;
    std::vector<City *> cities;
    cities.reserve(count);
    for (int i = 0; i < count; i++) {
        std::cin >> x >> y >> state;
        cities.push_back(new City(x, y, state));
    }
    double total_weight = sep_prim(cities);
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << total_weight << std::endl;
}

void phase2b() {
    double x, y, total_weight = 0;
    int state, count, last_state = -1;
    std::cin >> count;
    std::vector<std::vector<Node *>> nodes;
    for (int i = 0; i < count; i++) {
        std::cin >> x >> y >> state;
        if (state != last_state) {
            last_state = state;
            nodes.emplace_back();
        }
        nodes[state - 1].push_back(new Node(x, y, state));
    }
    int n = nodes.size();
    std::vector<KDTree *> kdtrees;
    kdtrees.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (nodes[i].size() < 2)
            continue;
        kdtrees[i] = new KDTree(2);
        auto kdtree = kdtrees[i];
        std::vector<Edge> edges;
        std::vector<Edge> MST;
        Node *first_node = kdtree->make(nodes[i]);
        first_node->in_fragment = true;
        kdtree->search_nearest(kdtree->root, first_node);

        edges.emplace_back(first_node, kdtree->nearest_node, kdtree->best_distance);
        make_heap(edges.begin(), edges.end(), &compare);

        while (kdtree->edges != MST.size()) {
            Edge &candidate_edge = edges.front();

            if (not candidate_edge.to->in_fragment) {
                Node *new_node_in_fragment = candidate_edge.to;
                new_node_in_fragment->in_fragment = true;
                MST.push_back(candidate_edge);
                total_weight += candidate_edge.distance;

                kdtree->delete_node(kdtree->root, nullptr, new_node_in_fragment);

                kdtree->nearest_node = nullptr;
                kdtree->search_nearest(kdtree->root, new_node_in_fragment);

                edges.emplace_back(new_node_in_fragment, kdtree->nearest_node, kdtree->best_distance);
                push_heap(edges.begin(), edges.end(), &compare);

            } else {
                Node *source_node = candidate_edge.from;

                pop_heap(edges.begin(), edges.end(), &compare);
                edges.pop_back();

                kdtree->nearest_node = nullptr;
                kdtree->search_nearest(kdtree->root, source_node);
                edges.emplace_back(source_node, kdtree->nearest_node, kdtree->best_distance);
                push_heap(edges.begin(), edges.end(), &compare);
            }
        }
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << total_weight << std::endl;
}

int main() {
    phase1a();
//    phase1b();
//    phase1c();
//    phase2a();
//    phase2b();
    return 0;
}
