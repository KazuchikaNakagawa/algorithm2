#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>

struct Edge {
    int to;
    unsigned weight;

    bool operator<(const Edge& other) const
    {
        return weight > other.weight;
    }

    bool operator>(const Edge& other) const
    {
        return weight < other.weight;
    }
};

struct Node {
    int identifier;
    std::vector<Edge> edges;

    Node(int identifier)
        : identifier(identifier)
    {
    }

    Node()
        : Node(-1)
    {
    } // default constructor;

    Node(const Node&) = default;
    Node& operator=(const Node&) = default;
    Node(Node&&) = default;

    void addEdge(int to, int weight)
    {
        Edge edge;
        edge.to = to;
        edge.weight = weight;
        edges.push_back(edge);
    }
};

class Graph {
    std::map<int, Node> nodes;

public:
    void addNode(int identifier)
    {
        Node node(identifier);
        nodes[identifier] = node;
    }
    void addEdge(int from, int to, int weight)
    {
        nodes[from].addEdge(to, weight);
        nodes[to].addEdge(from, weight);
    }
    void print()
    {
        for (const auto& pair : nodes) {
            std::cout << pair.first << ": ";
            for (const Edge& edge : pair.second.edges) {
                std::cout << edge.to << "(" << edge.weight << ") ";
            }
            std::cout << std::endl;
        }
    }

    int size() const
    {
        return nodes.size();
    }

    Node& operator[](int identifier)
    {
        return nodes[identifier];
    }

    friend void dijkstra_pq(Graph& g, int start, int end, std::vector<int>&);
};

#endif /* GRAPH_H */