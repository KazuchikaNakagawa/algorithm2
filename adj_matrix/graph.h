#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <iostream>
#include <vector>
struct Matrix {
    std::vector<std::vector<int>> matrix;

public:
    Matrix(int size)
    {
        matrix.resize(size);
        for (int i = 0; i < size; i++) {
            matrix[i].resize(size);
            std::fill(matrix[i].begin(), matrix[i].end(), 0);
        }
    }

    int& operator()(int i, int j)
    {
        return matrix[j][i];
    }
};

class Graph {
    Matrix adjMatrix;
    Matrix weights;

public:
    Graph(int size)
        : adjMatrix(size)
        , weights(size)
    {
        for (int i = 0; i < size; i++) {
            adjMatrix(i, i) = 1;
        }
        // print();
    }

    void addEdge(int from, int to, int weight)
    {
        adjMatrix(from, to) = 1;
        adjMatrix(to, from) = 1;
        weights(from, to) = weight;
        weights(to, from) = weight;
    }

    unsigned weight(int from, int to)
    {
        return weights(from, to);
    }

    int connected(int from, int to)
    {
        return from != to && adjMatrix(from, to) > 0;
    }

    int size() const
    {
        return adjMatrix.matrix.size();
    }

    void print()
    {
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                std::cout << adjMatrix(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif /* GRAPH_H */