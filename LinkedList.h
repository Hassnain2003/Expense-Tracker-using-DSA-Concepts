#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Expense.h"

struct Node {
    Expense data;
    Node* next;

    Node(const Expense& data);
};

class LinkedList {
private:
    Node* head;
    Node* tail;//last node

public:
    LinkedList();
    ~LinkedList();
    void insertExpense(const Expense& expense);
    void deleteExpense(double amount);
    void printExpenses() const;
    void saveToFile(ofstream& ofs) const;
    void loadFromFile(ifstream& ifs);
    Node* getHead() const;
    void clear();
    double totalAmount() const;
    void printList() const;
};

#endif // LINKEDLIST_H
