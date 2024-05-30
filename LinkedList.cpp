#include "LinkedList.h"
#include <iostream>
#include <sstream> // Include this for istringstream to read specific data from string file

Node::Node(const Expense& data)
    : data(data), next(nullptr) {
    // Constructor
}

LinkedList::LinkedList()
    : head(nullptr), tail(nullptr) {
    // Constructor
}
void LinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insertExpense(const Expense& expense) {
    Node* newNode = new Node(expense);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;// tail last node
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::deleteExpense(double amount) {
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data.getAmount() == amount) {
            if (prev == nullptr) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void LinkedList::printExpenses() const {
    Node* current = head;
    while (current != nullptr) {
        cout << "Amount: " << current->data.getAmount()
            << ", Date: " << current->data.getDate()
            << ", Description: " << current->data.getDescription()
            << endl;
        current = current->next;
    }
}

void LinkedList::saveToFile(ofstream& ofs) const {
    Node* current = head;
    while (current != nullptr) {
        ofs << current->data; // Use operator<< of Expense
        current = current->next;
    }
}

void LinkedList::loadFromFile(ifstream& ifs) {
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        Expense expense;
        iss >> expense; // Use operator>> of Expense
        insertExpense(expense);
    }
}

Node* LinkedList::getHead() const {
    return head;
}



double LinkedList::totalAmount() const {
    double total = 0.0;
    Node* current = head;
    while (current) {
        total += current->data.getAmount();
        current = current->next;
    }
    return total;
}

void LinkedList::printList() const {
    Node* current = head;
    while (current) {
        cout << "Transaction: " << current->data.getAmount() << " " << current->data.getDescription() << endl;
        current = current->next;
    }
}

