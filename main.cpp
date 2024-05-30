#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "User.h"
#include "Expense.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "PriorityQueue.h"
#include "ReportGenerator.h"
using namespace std;
// ANSI escape codes for coloring
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

void createAccount(HashTable& userTable) {
    string username, password, name, phoneNumber;
    double salary, fixedExpenses, desiredSavings;

    cout << CYAN << "Enter username: " << RESET;
    getline(cin, username);
    cout << CYAN << "Enter password: " << RESET;
    getline(cin, password);
    cout << CYAN << "Enter name: " << RESET;
    getline(cin, name);
    cout << CYAN << "Enter phone number Linked with your Bank Account: " << RESET;
    getline(cin, phoneNumber);
    cout << CYAN << "Enter salary: " << RESET;
    cin >> salary;
    while (true) {
        cout << CYAN << "Enter fixed expenses: " << RESET;
        cin >> fixedExpenses;
        if (fixedExpenses <= salary) {
            break; // Exit the loop if fixed expenses are valid
        }
        else {
            cout << RED << "Fixed expenses cannot be greater than salary. Please enter again." << RESET << endl;
        }
    }

    double remainingBalance = salary - fixedExpenses;
    while (true) {
        cout << CYAN << "Enter desired savings from remaining balance of " << remainingBalance << ": " << RESET;
        cin >> desiredSavings;
        if (desiredSavings <= remainingBalance) {
            break; // Exit the loop if desired savings are valid
        }
        else {
            cout << RED << "Desired savings cannot be greater than the remaining balance. Please enter again." << RESET << endl;
        }
    }

    User newUser(username, password);
    newUser.setName(name);
    newUser.setPhoneNumber(phoneNumber);
    newUser.setSalary(salary);
    newUser.setFixedExpenses(fixedExpenses);
    newUser.setDesiredSavings(desiredSavings);

    userTable.insertUser(newUser);

    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        newUser.saveToFile(userFile);
        userFile.close();
    }
    else {
        cerr << RED << "Unable to open file for writing user data." << RESET << endl;
    }
}

void enterExpenses(LinkedList& expenses, const User& currentUser) {
    double amount;
    string date, description, category;

    cout << BLUE << "Enter expense details:" << RESET << endl;
    cout << BLUE << "Amount: " << RESET;
    cin >> amount;
    cin.ignore(); // Clear the input buffer
    cout << BLUE << "Date (YYYY-MM-DD): " << RESET;
    getline(cin, date);
    cout << BLUE << "Category: " << RESET;
    getline(cin, category);
    cout << BLUE << "Description: " << RESET;
    getline(cin, description);

    Expense newExpense(amount, date, description, currentUser.getUsername());
    newExpense.setCategory(category);

    expenses.insertExpense(newExpense);

    ofstream expenseFile("expenses.txt", ios::app);
    if (expenseFile.is_open()) {
        newExpense.saveToFile(expenseFile);
        expenseFile.close();
    }
    else {
        cerr << RED << "Unable to open file for writing expense data." << RESET << endl;
    }
}

void displayFetchedMessages(PriorityQueue& messages) {
    cout << GREEN << "Fetched messages from bank:" << RESET << endl;
    messages.print();
}

void showTopExpenses(PriorityQueue& expenses, int n) {
    if (expenses.isEmpty()) {
        cout << RED << "No expenses to show." << RESET << endl;
        return;
    }

    PriorityQueue tempQueue = expenses; // Create a copy to preserve the original queue
    cout << GREEN << "Top " << n << " Expenses:" << RESET << endl;
    for (int i = 0; i < n && !tempQueue.isEmpty(); ++i) {
        Expense topExpense = tempQueue.dequeue();
        cout << topExpense.getCategory() << ": " << topExpense.getAmount() << " on " << topExpense.getDate() << endl;
    }
}

void showLowestExpenses(PriorityQueue& expenses, int n) {
    if (expenses.isEmpty()) {
        cout << RED << "No expenses to show." << RESET << endl;
        return;
    }

    PriorityQueue tempQueue = expenses; // Create a copy to preserve the original queue
    tempQueue = PriorityQueue(false); // Reinitialize as a max heap
    cout << GREEN << "Lowest " << n << " Expenses:" << RESET << endl;
    for (int i = 0; i < n && !tempQueue.isEmpty(); ++i) {
        Expense lowestExpense = tempQueue.dequeue();
        cout << lowestExpense.getCategory() << ": " << lowestExpense.getAmount() << " on " << lowestExpense.getDate() << endl;
    }
}
void generateReport(const User& currentUser, const LinkedList& expenses, const PriorityQueue& messages) {
    double totalExpenses = expenses.totalAmount();

    // Sum up fetched messages expenses
    double totalFetchedExpenses = 0.0;
    PriorityQueue tempMessages = messages;
    while (!tempMessages.isEmpty()) {
        Expense fetchedExpense = tempMessages.dequeue();
        totalFetchedExpenses += fetchedExpense.getAmount();
    }

    double remainingBalance = currentUser.getSalary() - currentUser.getFixedExpenses();
    double totalVariableExpenses = totalExpenses + totalFetchedExpenses;
    double savedAmount = remainingBalance - totalVariableExpenses;
    double desiredSavings = currentUser.getDesiredSavings();

    cout << "Expense Report for User: " << currentUser.getUsername() << endl;
    cout << "Total Variable Expenses: " << totalVariableExpenses << endl;
    cout << "Desired Savings: " << desiredSavings << endl;
    cout << "Saved Amount: " << savedAmount << endl;

    if (savedAmount >= desiredSavings) {
        cout << "You are on the right track!" << endl;
    }
    else {
        cout << "You are on the wrong track. Try to reduce your expenses." << endl;
    }
}



int main() {
    HashTable userTable;
    LinkedList expenses;
    PriorityQueue messages;
    PriorityQueue expenseQueue; // For top and lowest expenses
    ReportGenerator reportGenerator;

    // Load existing user data
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        while (!userFile.eof()) {
            User user;
            user.loadFromFile(userFile);
            userTable.insertUser(user);
        }
        userFile.close();
    }

    // Load existing expenses
    ifstream expenseFile("expenses.txt");
    if (expenseFile.is_open()) {
        while (!expenseFile.eof()) {
            Expense expense;
            expense.loadFromFile(expenseFile);
            expenses.insertExpense(expense);
            expenseQueue.enqueue(expense); // Add to priority queue
        }
        expenseFile.close();
    }

    int choice;
    User currentUser;
    bool exit = false;
    bool fetchedMessagesProcessed = false;

    while (!exit) {
        if (!currentUser.isLoggedIn()) {
            // Menu options for users who are not logged in
            cout << "\nWelcome to Expense Tracker!" << endl;
            cout << "1. Create Account" << endl;
            cout << "2. Log In" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear the input buffer

            switch (choice) {
            case 1: // Create Account
                createAccount(userTable);
                break;

            case 2: // Log In
                if (!currentUser.isLoggedIn()) {
                    string username, password;
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);

                    User userToFind(username, password);
                    User* foundUser = userTable.findUser(userToFind);

                    if (foundUser != nullptr) {
                        currentUser = *foundUser;
                        currentUser.login();
                        cout << "Login successful!" << endl;

                        // Fetch messages for the logged in user if not processed yet
                        if (!fetchedMessagesProcessed) {
                            vector<string> messagesData = {
                                "50.0,2024-05-28,Lunch,Food",
                                "150.0,2024-05-27,Groceries,Shopping",
                                "30.0,2024-05-26,Gas,Transportation",
                                "200.0,2024-05-25,Dinner,Food"
                            };

                            for (const auto& message : messagesData) {
                                istringstream iss(message);
                                string token;

                                // Tokenize the message
                                getline(iss, token, ','); // Amount
                                double amount = stod(token);

                                getline(iss, token, ','); // Date
                                string date = token;

                                getline(iss, token, ','); // Description
                                string description = token;

                                getline(iss, token, ','); // Category
                                string category = token;

                                Expense newExpense(amount, date, description, currentUser.getUsername());
                                newExpense.setCategory(category);

                                messages.enqueue(newExpense);
                                expenseQueue.enqueue(newExpense); // Add to expense priority queue
                            }

                            fetchedMessagesProcessed = true;
                        }
                    }
                    else {
                        cout << "Login failed. User not found." << endl;
                    }
                }
                else {
                    cout << "You are already logged in as " << currentUser.getUsername() << endl;
                }
                break;

            case 3: // Exit
                exit = true;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
        else {
            // Menu options for users who are logged in
            cout << "\nWelcome back, " << currentUser.getUsername() << "!" << endl;
            cout << "1. Generate Report" << endl;
            cout << "2. Display Fetched Messages" << endl;
            cout << "3. Add Expense Manually" << endl;
            cout << "4. Show Top Expenses" << endl;
            cout << "5. Log Out" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear the input buffer

            switch (choice) {
            case 1: // Generate Report
                generateReport(currentUser, expenses, messages);
                break;

            case 2: // Display Fetched Messages
                displayFetchedMessages(messages);
                break;

            case 3: // Add Expense Manually
                enterExpenses(expenses, currentUser);
                break;

            case 4: // Show Top Expenses
            {
                int n;
                cout << "Enter number of top expenses to show: ";
                cin >> n;
                showTopExpenses(expenseQueue, n);
            }
            break;


            case 5: // Log Out
                currentUser.logout();
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

    cout << "Exiting Expense Tracker. Goodbye!" << endl;
    return 0;
}

