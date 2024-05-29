#include "../data_provider.h"
#include "graph.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

void dijkstra_matrix(Graph& g, int start, int end, std::vector<int>& result)
{
    std::vector<unsigned> dist(g.size(), INT_MAX);
    std::map<int, unsigned> prev;
    std::vector<bool> visited(g.size(), false);

    dist[start] = 0;
    while (true) {
        unsigned min = INT_MAX;
        int nextVertex = -1;
        for (int i = 0; i < g.size(); i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                nextVertex = i;
            }
        }

        if (nextVertex == -1) {
            break;
        }

        visited[nextVertex] = true;
        // std::cout << "visited: " << nextVertex << std::endl;
        for (int i = 0; i < g.size(); i++) {
            if (g.connected(nextVertex, i)) {
                // std::cout << nextVertex << " connected: " << i << std::endl;
                unsigned newDist = dist[nextVertex] + g.weight(nextVertex, i);
                if (newDist < dist[i]) {
                    // std::cout << "new dist: " << newDist << " from " << nextVertex << " to " << i << std::endl;
                    dist[i] = newDist;
                    prev[i] = nextVertex;
                }
            }
        }
    }

    // print prev
    // for (const auto& pair : prev) {
    //     std::cout << pair.first << " <- " << pair.second << std::endl;
    // }

    int current = end;
    while (current != start) {
        result.push_back(current);
        if (prev.find(current) == prev.end()) {
            result.clear();
            return;
        }
        current = prev[current];
    }
    result.push_back(current);
}

int main(int argc, char** argv)
{
    DataProvider provider("..");

    Graph g(120);
    for (int i = 0; i < 120; i++) {
        auto* data = provider[i];
        for (const auto& link : data->links) {
            g.addEdge(i, link->identifier, abs(data->size() - link->size()) + 1);
        }
    }

    // g.print();

    std::vector<int> result;
    int startW = std::stoi(argv[1]);
    int endW = std::stoi(argv[2]);

    auto start = clock();
    dijkstra_matrix(g, startW, endW, result);
    auto end = clock();
    for (auto vertex = result.rbegin(); vertex != result.rend(); vertex++) {
        std::cout << provider[*vertex]->word << "(" << provider[*vertex]->size() << ")";
        if (vertex + 1 != result.rend()) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    std::cout << "Time: " << (end - start) / (double)CLOCKS_PER_SEC << std::endl;
    return 0;
}