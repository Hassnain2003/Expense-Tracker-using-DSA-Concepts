#include "Expense.h"

Expense::Expense(double amount, const string& date, const string& description, const string& username)
    : amount(amount), date(date), description(description), category(""), username(username) {}

double Expense::getAmount() const {
    return amount;
}

string Expense::getDate() const {
    return date;
}

string Expense::getDescription() const {
    return description;
}

string Expense::getCategory() const {
    return category;
}

string Expense::getUsername() const {
    return username;
}

void Expense::setCategory(const string& category) {
    this->category = category;
}

void Expense::saveToFile(ofstream& file) const {
    file << amount << "\n" << date << "\n" << description << "\n" << category << "\n" << username << "\n";
}

void Expense::loadFromFile(ifstream& file) {
    getline(file, date);
    file >> amount;
    file.ignore(); // To ignore the newline character after reading double value
    getline(file, description);
    getline(file, category);
    getline(file, username);
}

