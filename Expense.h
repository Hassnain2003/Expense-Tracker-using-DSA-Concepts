#ifndef EXPENSE_H
#define EXPENSE_H
using namespace std;
#include <string>
#include <fstream>

class Expense {
private:
    double amount;
    string date;
    string description;
    string category;
    string username;

public:
    Expense(double amount = 0.0, const string& date = "", const string& description = "", const string& username = "");

    double getAmount() const;
    string getDate() const;
    string getDescription() const;
    string getCategory() const;
    string getUsername() const;

    void setCategory(const string& category);

    // Serialization methods
    void saveToFile(ofstream& file) const;
    void loadFromFile(ifstream& file);
    friend ostream& operator<<(ostream& os, const Expense& expense) {
        os << expense.amount << "," << expense.date << "," << expense.description << "," << expense.username << "," << expense.category << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Expense& expense) {
        getline(is, expense.date, ',');
        is >> expense.amount;
        is.ignore();
        getline(is, expense.description, ',');
        getline(is, expense.username, ',');
        getline(is, expense.category);
        return is;
    }
};

#endif // EXPENSE_H

