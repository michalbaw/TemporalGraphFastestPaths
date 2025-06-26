#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

#include "time_measuring.hpp"

#define INF INT_MAX/2

void getShortestPath(std::vector<std::tuple<int,int,int,int>> const& graph, const int graphSize, const int a, std::vector<int>& results);

int main ()
{
    int n;
    unsigned m, tries;
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

void getSinglePath(std::vector<std::tuple<int,int,int,int>> const& graph, const int graphSize, const int a, const int t0, std::vector<int>& results);

void getShortestPath(std::vector<std::tuple<int,int,int,int>> const& graph, const int graphSize, const int a, std::vector<int>& results)
{
    for (auto& i : results) {
        i = INF;
    }
    results[a] = 0;

    std::vector<int> beginTimes;
    for (auto [t, l, u, v] : graph) {
        if (u == a) {
            if (beginTimes.empty() || beginTimes[beginTimes.size()-1] != t) {
                beginTimes.push_back(t);
            }
        }
    }

    int bestTime = INF;

    std::vector<int> thisTime(graphSize);

    for (int i : beginTimes) {
        getSinglePath(graph, graphSize, a, i, thisTime);
        for (int j = 0; j < graphSize; j++) {
            results[j] = std::min(results[j], thisTime[j]);
        }
    }
}

void getSinglePath(std::vector<std::tuple<int,int,int,int>> const& graph, const int graphSize, const int a, const int t0, std::vector<int>& results)
{
    for (auto& i : results) {
        i = INF;
    }
    results[a] = t0;
    for (auto [t, l, u, v] : graph) {
        if (t < results[u]) {
            continue;
        }
        if (t+l < results[v]) {
            results[v] = t+l;
        }
    }
}