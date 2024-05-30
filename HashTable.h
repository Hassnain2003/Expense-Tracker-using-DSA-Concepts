#ifndef HASHTABLE_H
#define HASHTABLE_H
using namespace std;
#include "User.h"
#include <list>
#include <vector>

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<User>> table;

public:
    HashTable();

    void insertUser(const User& user);
    User* findUser(const User& user);
};

#endif // HASHTABLE_H
