#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

class PriorityQueue {
    std::vector<int> heap;
    std::vector<int> index;
    std::vector<int> key;

public:
    void downHeap(int i)
    {
        int v = heap[i];
        int j;
        while (i <= heap.size() / 2) {
            j = i * 2;
        }
    }
};

#endif /* PRIORITY_QUEUE_H */