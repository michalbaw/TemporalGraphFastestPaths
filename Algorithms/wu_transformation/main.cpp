#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
#include <map>
#include <unordered_set>
#include <queue>

#include "time_measuring.hpp"
#include "io.hpp"

#define INF INT_MAX/2

namespace std
{
    template<class A, class B, class C>
    struct hash<tuple<A,B,C>>{
        size_t operator() (const tuple<A,B,C>& p) const {
            return std::rotl(hash<A>{}(get<0>(p)),2) ^
                std::rotl(hash<B>{}(get<1>(p)),1) ^
                hash<C>{}(get<2>(p));
        }
    };
}

struct node
{
    int vertex_no;
    bool isOutNode;
    std::vector<std::map<int,node>::iterator> edges;

    node(int v, bool o): vertex_no(v), isOutNode(o) {}
};

using graph_t = std::vector<std::pair<std::map<int,node>,std::map<int,node>>>;

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
    graph_t g(graphSize);
    for (auto [time, l, a, b] : graph) {
        auto outNode = g[a].second.insert(std::pair{time, node(a, true)}).first;
        auto inNode = g[b].first.insert(std::pair{time+l, node(b, false)}).first;
        outNode->second.edges.push_back(inNode);
    }

    for (auto& v : g) {
        auto i1 = v.first.begin();
        auto i2 = v.second.begin();
        
        while (i1 != v.first.end() && i2 != v.second.end()) {
            if (i2->first < i1->first) {
                i2++;
                continue;
            }
            i1->second.edges.push_back(i2);
            i1++;
        }
    }

    return g;
}

void getShortestPaths(graph_t& graph, int beginPoint, std::vector<int>& results)
{
    for (auto& i : results) {
        i = INF;
    }
    results[beginPoint] = 0;
    std::unordered_set<std::tuple<int,int,bool>> visited;
    for (auto it = graph[beginPoint].second.end(); it != graph[beginPoint].second.begin(); ) {
        it--;
        std::queue<std::map<int,node>::iterator> q;
        q.push(it);

        while(!q.empty()) {
            auto const e = q.front();
            q.pop();
            auto wasInserted = visited.insert(std::tuple(e->second.vertex_no, e->first, e->second.isOutNode)).second;
            if (!wasInserted) {
                continue;
            }
            // std::print("Vertex: {} {}, with begin: {}\n", e->second.vertex_no, e->first, it->first);
            results[e->second.vertex_no] = std::min(results[e->second.vertex_no], e->first - it->first);
            auto it_copy = e;
            ++it_copy;

            if (it_copy != graph[e->second.vertex_no].first.end() && it_copy != graph[e->second.vertex_no].second.end()) {
                q.push(it_copy);
            }
            q.push_range(e->second.edges);
        }
    }
}