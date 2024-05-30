#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
using namespace std;
#include <vector>
#include "LinkedList.h"
#include "User.h"

struct ExpenseSummary {
    string username;
    double totalExpenses;
    double averageExpense;
};

class ReportGenerator {
private:
    vector<ExpenseSummary> expenseSummaries;

public:
    void addExpense(const Expense& expense);
    void generateReports(LinkedList& expenses, const User& user);
};

#endif // REPORTGENERATOR_H
