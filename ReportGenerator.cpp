#include "ReportGenerator.h"
#include <iostream>

void ReportGenerator::addExpense(const Expense& expense) {
    bool found = false;
    for (auto& summary : expenseSummaries) {
        if (summary.username == expense.getUsername()) {
            summary.totalExpenses += expense.getAmount();
            summary.averageExpense = summary.totalExpenses / expenseSummaries.size();
            found = true;
            break;
        }
    }

    if (!found) {
        // If not found, add new user summary
        ExpenseSummary newSummary;
        newSummary.username = expense.getUsername();
        newSummary.totalExpenses = expense.getAmount();
        newSummary.averageExpense = expense.getAmount();
        expenseSummaries.push_back(newSummary);
    }
}

void ReportGenerator::generateReports(LinkedList& expenses, const User& user) {
    double totalExpenses = 0.0;
    Node* current = expenses.getHead();

    while (current != nullptr) {
        if (current->data.getUsername() == user.getUsername()) {
            totalExpenses += current->data.getAmount();
        }
        current = current->next;
    }

    double remainingAmount = user.getSalary() - user.getFixedExpenses() - totalExpenses;
    double savedAmount = remainingAmount - user.getDesiredSavings();

    cout << "Expense Report for User: " << user.getName() << endl;
    cout << "Total Expenses: " << totalExpenses << endl;
    cout << "Remaining Amount: " << remainingAmount << endl;
    cout << "Desired Savings: " << user.getDesiredSavings() << endl;
    cout << "Saved Amount: " << savedAmount << endl;
}

