#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "shewedpolo/City.hpp"

#define INF MAXFLOAT

struct Edge {
    float w = INF;
    int to = -1;
};

float prim(std::vector<City *> &cities) {
    float total_weight = 0;
    int n = cities.size();
    std::vector<bool> selected(n, false);
    std::vector<Edge> min_e(n);
    min_e[0].w = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (not selected[j] and (v == -1 or min_e[j].w < min_e[v].w))
                v = j;
        }
        if (min_e[v].w == INF) {
            std::cout << "No MST!" << std::endl;
            return 0;
        }
        selected[v] = true;
        total_weight += min_e[v].w;
//        if (min_e[v].to != -1)
//            std::cout << v + 1 << " " << min_e[v].to + 1 << std::endl;
        for (int to = 0; to < n; ++to) {
            if (cities[v]->distance(cities[to]) < min_e[to].w)
                min_e[to] = {cities[v]->distance(cities[to]), v};
        }
    }
    return total_weight;
}

float state_prim(std::vector<std::vector<City *>> &states) {
    float total_weight = 0;
    int n = states.size();
    std::vector<bool> selected(n, false);
    std::vector<Edge> min_e(n);
    min_e[0].w = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (not selected[j] and (v == -1 or min_e[j].w < min_e[v].w))
                v = j;
        }
        if (min_e[v].w == INF) {
            std::cout << "No MST!" << std::endl;
            return 0;
        }
        selected[v] = true;
        total_weight += min_e[v].w;
        int this_state = states[v].size();
        for (int ts = 0; ts < this_state; ++ts)
            for (int to = 0; to < n; ++to) {
                int ct = states[to].size();
                for (int t = 0; t < ct; ++t)
                    if (states[v][ts]->distance(states[to][t]) < min_e[to].w)
                        min_e[to] = {states[v][ts]->distance(states[to][t]), v};
            }
    }
    return total_weight;
}

float sep_prim(std::vector<City *> &cities) {
    int n = cities[cities.size() - 1]->getState();
    std::vector<std::vector<City *>> states(n);
    for (auto &city: cities) {
        states[city->getState() - 1].push_back(city);
    }
    float total_weight = 0;
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
                float dis = cities[i]->distance(cities[j]);
                if (dis > cities[i]->getMaxDis()) {
                    cities[i]->setMaxDis(dis);
                }
            }
        }
        float min_dis = INF;
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

int main() {
    int n, s;
    float x, y;
    std::cin >> n;
    std::vector<City *> cities;
    cities.reserve(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y >> s;
        cities.push_back(new City(x, y, s));
    }
//    find_capitals(cities);
//    float total_weight = prim(cities);
    float total_weight = sep_prim(cities);
//    std::cout << std::fixed;
//    std::cout << std::setprecision(2);
//    std::cout << total_weight << std::endl;
    printf("%.2f\n", total_weight);
    return 0;
}
