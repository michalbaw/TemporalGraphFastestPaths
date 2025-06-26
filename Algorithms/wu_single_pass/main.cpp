#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
#include <map>
#include <unordered_map>

#include "time_measuring.hpp"

#define INF INT_MAX/2

void getShortestPath(std::vector<std::tuple<int,int,int,int>> const& graph, unsigned graphSize, const int a, std::vector<int>& results);

int main ()
{
    int n, m;
    unsigned tries;
    std::cin >> n >> m >> tries;
    std::vector<std::tuple<int,int,int,int>> graph (m);
    for (auto& i : graph) {
        auto& [time, l, a, b] = i;
        std::cin >> a >> b >> time >> l;
    }
    std::vector<std::vector<int>> results(tries, std::vector<int>(n));
    std::sort(graph.begin(), graph.end());

    TimeCounter timeCounter;

    timeCounter.begin();

    for (int i = 0; i < tries; i++) {
        int a;
        std::cin >> a;
        getShortestPath(graph, n, a, results[i]);
    }

    timeCounter.end();

    for (auto& i : results) {
        for (auto j : i) {
            std::print("{} ", j);
        }
        std::print("\n");
    }

    std::print(std::cerr, "{}\n", timeCounter);
}

void getShortestPath(std::vector<std::tuple<int,int,int,int>> const& graph, unsigned graphSize, const int a, std::vector<int>& results)
{
    for (auto& i : results) {
        i = INF;
    }
    results[a] = 0;

    std::vector<std::map<int,int>> la(graphSize);
    std::vector<std::unordered_map<int,int>> ls(graphSize);

    for (auto [t, l, u, v] : graph) {
        if (u == a) {
            la[u][t] = t;
            ls[u][t] = t;
        }
        auto it_au = la[u].upper_bound(t);
        if (it_au == la[u].begin()) {
            continue;
        }
        it_au--;
        int av = t+l, sv = it_au->second;
        if (ls[v].contains(sv)) {
            if (ls[v][sv] <= av) {
                continue;
            }
            la[v].erase(ls[v][sv]);
        }
        ls[v][sv] = av;
        la[v][av] = sv;
        auto dominated_it = la[v].upper_bound(av);
        while (dominated_it != la[v].end()) {
            if (dominated_it->second <= sv) {
                ls[v].erase(dominated_it->second);
                auto it_copy = dominated_it;
                dominated_it++;
                la[v].erase(it_copy);
            }
            else {
                dominated_it++;
            }
        }
        results[v] = std::min(results[v], av-sv);
    }
}