#include "HashTable.h"
#include <functional>

HashTable::HashTable() : table(TABLE_SIZE) {}

void HashTable::insertUser(const User& user) {
    int index = hash<string>{}(user.getUsername()) % TABLE_SIZE;
    table[index].push_back(user);
}

User* HashTable::findUser(const User& user) {
    int index = hash<string>{}(user.getUsername()) % TABLE_SIZE;

    for (auto& u : table[index]) {
        if (u == user) { // Using the equality operator
            return &u;
        }
    }

    return nullptr;
}

