#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
#include <flat_map>
#include <unordered_set>
#include <queue>

#include "time_measuring.hpp"
#include "io.hpp"

#define INF INT_MAX/2

namespace std
{
    template<class A,class B>
    struct hash<pair<A,B>>{
        size_t operator() (const pair<A,B>& p) const {
            return std::rotl(hash<A>{}(p.first),1) ^
                hash<B>{}(p.second);
        }
    };
}

struct node
{
    int vertex_no;
    std::vector<std::pair<std::flat_map<int,node>::iterator, int>> edges;

    node(int v): vertex_no(v) {}
};

using graph_t = std::vector<std::flat_map<int,node>>;

graph_t transform(std::vector<std::tuple<int,int,int,int>> const& graph, unsigned graphSize);

void getShortestPaths(graph_t& graph, int beginPoint, std::vector<int>& results);

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

    auto newGraph = transform(graph, n);

    for (int i = 0; i < tries; i++) {
        int a;
        std::cin >> a;
        getShortestPaths(newGraph, a, results[i]);
    }

    timeCounter.end();

    printResults(results);

    std::print(std::cerr, "{}\n", timeCounter);
}

graph_t transform(std::vector<std::tuple<int,int,int,int>> const& graph, unsigned graphSize)
{
    graph_t g {graphSize};
    for (auto [time, l, a, b] : graph) {
        g[a].insert(std::pair(time, node(a)));
    }

    for (auto [time, l, a, b] : graph) {
        auto outNode = g[a].lower_bound(time);
        auto inNode = g[b].lower_bound(time+l);
        if (inNode == g[b].end()) {
            inNode = g[b].insert(std::pair(INF, node(b))).first;
        }
        outNode->second.edges.push_back(std::pair(inNode, time+l));
    }

    return g;
}


void getShortestPaths(graph_t& graph, int beginPoint, std::vector<int>& results)
{
    for (auto& i : results) {
        i = INF;
    }
    results[beginPoint] = 0;
    std::unordered_set<std::pair<int,int>> visited{};
    for (auto it = graph[beginPoint].end(); it != graph[beginPoint].begin(); ) {
        it--;
        std::queue<std::pair<std::flat_map<int,node>::iterator,int>> q;
        q.push(std::make_pair(it, it->first));

        while(!q.empty()) {
            auto [e, t] = q.front();
            q.pop();
            auto wasInserted = visited.insert({e->second.vertex_no, e->first}).second;
            if (!wasInserted) {
                continue;
            }
            results[e->second.vertex_no] = std::min(results[e->second.vertex_no], t - it->first);
            auto it_copy = e;
            it_copy++;
            if (it_copy != graph[e->second.vertex_no].end()) {
                q.push({it_copy, it_copy->first});
            }
            q.push_range(e->second.edges);
        }
    }
}