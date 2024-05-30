#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
using namespace std;
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Expense.h"

class PriorityQueue {
private:
    vector<Expense> heap;
    bool isMinHeap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    bool compare(const Expense& a, const Expense& b) const;
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }

public:
    PriorityQueue(bool minHeap = true) : isMinHeap(minHeap) {}
    void enqueue(const Expense& expense); // Renamed from insert
    Expense dequeue(); // Renamed from extract
    void print() const;
    bool isEmpty() const; // Renamed from empty
};

#endif // PRIORITY_QUEUE_H
