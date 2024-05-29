#include "../data_provider.h"
#include "graph.h"
#include <climits>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

void bellman_ford(Graph& g, int start, int end, std::vector<int>& result)
{
    std::vector<unsigned> dist(g.size(), INT_MAX);
    std::map<int, unsigned> prev;

    dist[start] = 0;

    bool updated = false;
    while (true) {
        updated = false;
        for (int i = 0; i < g.size(); i++) {
            // std::cout << "visit: " << i << std::endl;
            Node& node = g[i];
            for (Edge& e : node.edges) {
                // std::cout << "edge: " << e.to << std::endl;
                unsigned newDist = dist[i] + e.weight;
                if (newDist < dist[e.to]) {
                    dist[e.to] = newDist;
                    prev[e.to] = i;
                    // std::cout << "new dist: " << newDist << " from " << i << " to " << e.to << std::endl;
                    updated = true;
                }
            }
        }
        if (!updated) {
            break;
        }
    }

    int current = end;
    while (current != start) {
        result.push_back(current);
        current = prev[current];
    }
    result.push_back(current);
}

int main(int argc, char** argv)
{
    DataProvider provider("..");
    Graph g;

    for (int i = 0; i < 120; i++) {
        g.addNode(i);
    }
    for (int i = 0; i < 120; i++) {
        for (const auto edge : provider[i]->links) {
            g.addEdge(i, edge->identifier, abs(edge->size() - provider[i]->size()) + 1);
        }
    }

    std::vector<int> result;
    int startW = std::stoi(argv[1]);
    int endW = std::stoi(argv[2]);

    auto start = clock();
    bellman_ford(g, startW, endW, result);
    auto end = clock();
    for (auto iter = result.rbegin(); iter != result.rend(); iter++) {
        std::cout << provider[*iter]->word << "(" << provider[*iter]->size() << ")";
        if (iter + 1 != result.rend()) {
            std::cout << " -> ";
        } else {
            std::cout << std::endl;
        }
    }
    std::cout << "Time: " << (end - start) / (double)CLOCKS_PER_SEC << std::endl;
    return 0;
}