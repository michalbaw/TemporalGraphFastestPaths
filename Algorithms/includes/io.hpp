#pragma once

#include <vector>
#include <print>
#include <climits>

#define INF INT_MAX/2

void printResults(std::vector<std::vector<int>> const& res)
{
    for (auto& i : res) {
        for (auto j : i) {
            std::print("{}\n", j == INF ? -10 : j);
        }
        std::print("\n");
    }
}