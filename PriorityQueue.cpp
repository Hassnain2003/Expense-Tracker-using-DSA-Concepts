#include "PriorityQueue.h"

void PriorityQueue::heapifyUp(int index) {
    if (index > 0 && compare(heap[parent(index)], heap[index])) {
        swap(heap[index], heap[parent(index)]);
        heapifyUp(parent(index));
    }
}

void PriorityQueue::heapifyDown(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int smallestOrLargest = index;

    if (left < heap.size() && compare(heap[smallestOrLargest], heap[left])) {
        smallestOrLargest = left;
    }

    if (right < heap.size() && compare(heap[smallestOrLargest], heap[right])) {
        smallestOrLargest = right;
    }

    if (smallestOrLargest != index) {
        swap(heap[index], heap[smallestOrLargest]);
        heapifyDown(smallestOrLargest);
    }
}

bool PriorityQueue::compare(const Expense& a, const Expense& b) const {
    if (isMinHeap) {
        return a.getAmount() < b.getAmount();
    }
    else {
        return a.getAmount() > b.getAmount();
    }
}

void PriorityQueue::enqueue(const Expense& expense) {
    heap.push_back(expense);
    int index = heap.size() - 1;
    heapifyUp(index);
}

Expense PriorityQueue::dequeue() {
    if (heap.empty()) {
        throw runtime_error("Priority queue is empty");
    }

    Expense root = heap.front();
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);

    return root;
}

void PriorityQueue::print() const {
    for (const auto& expense : heap) {
        cout << expense.getCategory() << ": " << expense.getAmount() << endl;
    }
}

bool PriorityQueue::isEmpty() const {
    return heap.empty();
}

