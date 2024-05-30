#include "User.h"
#include <iostream>

User::User()
    : username(""), password(""), loggedIn(false), name(""), phoneNumber(""),
    salary(0.0), fixedExpenses(0.0), desiredSavings(0.0) {}

User::User(const string& username, const string& password)
    : username(username), password(password), loggedIn(false), name(""), phoneNumber(""),
    salary(0.0), fixedExpenses(0.0), desiredSavings(0.0) {}

string User::getUsername() const {
    return username;
}

void User::setUsername(const string& username) {
    this->username = username;
}

string User::getPassword() const {
    return password;
}

void User::setPassword(const string& password) {
    this->password = password;
}

bool User::isLoggedIn() const {
    return loggedIn;
}

void User::login() {
    loggedIn = true;
}

void User::logout() {
    loggedIn = false;
}

string User::getName() const {
    return name;
}

void User::setName(const string& name) {
    this->name = name;
}

string User::getPhoneNumber() const {
    return phoneNumber;
}

void User::setPhoneNumber(const string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

double User::getSalary() const {
    return salary;
}

void User::setSalary(double salary) {
    this->salary = salary;
}

double User::getFixedExpenses() const {
    return fixedExpenses;
}

void User::setFixedExpenses(double expenses) {
    this->fixedExpenses = expenses;
}

double User::getDesiredSavings() const {
    return desiredSavings;
}

void User::setDesiredSavings(double savings) {
    this->desiredSavings = savings;
}

bool User::operator==(const User& other) const {
    return username == other.username && password == other.password;
}

void User::saveToFile(ofstream& file) const {
    file << username << "\n" << password << "\n" << name << "\n" << phoneNumber << "\n"
        << salary << "\n" << fixedExpenses << "\n" << desiredSavings << "\n";
}

void User::loadFromFile(ifstream& file) {
    getline(file, username);
    getline(file, password);
    getline(file, name);
    getline(file, phoneNumber);
    file >> salary >> fixedExpenses >> desiredSavings;
    file.ignore(); // To ignore the newline character after reading double values
}

