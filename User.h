#ifndef USER_H
#define USER_H
using namespace std;
#include <string>
#include <fstream>

class User {
private:
    string username;
    string password;
    bool loggedIn;
    string name;
    string phoneNumber;
    double salary;
    double fixedExpenses;
    double desiredSavings;

public:
    User();
    User(const string& username, const string& password);

    string getUsername() const;
    void setUsername(const string& username);

    string getPassword() const;
    void setPassword(const string& password);

    bool isLoggedIn() const;
    void login();
    void logout();

    string getName() const;
    void setName(const string& name);

    string getPhoneNumber() const;
    void setPhoneNumber(const string& phoneNumber);

    double getSalary() const;
    void setSalary(double salary);

    double getFixedExpenses() const;
    void setFixedExpenses(double expenses);

    double getDesiredSavings() const;
    void setDesiredSavings(double savings);
    bool operator==(const User& other) const; // Equality operator

    // Serialization methods
    void saveToFile(ofstream& file) const;
    void loadFromFile(ifstream& file);
};

#endif // USER_H

