#include "../data_provider.h"
#include "graph.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

void dijkstra_pq(Graph& g, int start, int end, std::vector<int>& result)
{
    std::priority_queue<Edge> pq;
    std::map<int, int> prev;
    std::vector<unsigned> dist(g.size(), INT_MAX);

    for (const auto& pair : g.nodes) {
        dist[pair.first] = INT_MAX;
    }

    pq.push({ start, 0 });

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();

        for (Edge& e : g[edge.to].edges) {
            unsigned newDist = (unsigned)edge.weight + (unsigned)e.weight;
            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                e.weight = newDist;
                pq.push({ e.to, newDist });
                prev[e.to] = edge.to;
            }
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
    dijkstra_pq(g, startW, endW, result);
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