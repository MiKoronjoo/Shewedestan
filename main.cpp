#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "shewedpolo/City.hpp"

#define INF INT32_MAX

struct Edge {
    float w = INT64_MAX;
    int to = -1;
};

void prim(std::vector<City> &cities) {
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
        if (min_e[v].w == INT64_MAX) {
            std::cout << "No MST!" << std::endl;
            return;
        }
        selected[v] = true;
        total_weight += min_e[v].w;
        if (min_e[v].to != -1)
            std::cout << v + 1 << " " << min_e[v].to + 1 << std::endl;
        for (int to = 0; to < n; ++to) {
            if (cities[v].distance(cities[to]) < min_e[to].w)
                min_e[to] = {cities[v].distance(cities[to]), v};
        }
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << total_weight << std::endl;
}

void find_capitals(std::vector<City> &cities) {
    int n = cities.size();
    std::vector<std::vector<int>> indexes(n);
    for (int i = 0; i < n; i++) {
        indexes[cities[i].getState() - 1].push_back(i);
    }
    for (const auto &state: indexes) {
        if (state.empty())
            continue;
        float x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;
        for (int i: state) {
            if (cities[i].getX() > x1)
                x1 = cities[i].getX();
            if (cities[i].getX() < x0)
                x0 = cities[i].getX();
            if (cities[i].getY() > y1)
                y1 = cities[i].getY();
            if (cities[i].getY() < y0)
                y0 = cities[i].getY();
        }
        float x = (x1 - x0) / 2;
        float y = (y1 - y0) / 2;
        float min_dis = INF;
        int j = -1;
        for (int i: state) {
            if (cities[i].distance(x, y) < min_dis) {
                min_dis = cities[i].distance(x, y);
                j = i;
            }
        }
        cities[j].setIsCapital(true);
        std::cout << "Capital of State " << cities[j].getState() << ": " << j + 1 << std::endl;
    }
}

int main() {
    int n, s;
    float x, y;
    std::cin >> n;
    std::vector<City> cities;
    cities.reserve(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y >> s;
        cities.emplace_back(x, y, s);
    }
    find_capitals(cities);
//    prim(cities);
    std::cout << "Hello Faraz!!" << std::endl;
    return 0;
}
