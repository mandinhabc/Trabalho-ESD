#include "hashtable.hpp"
#include <iostream>


HashTable::HashTable() : table(TABLE_SIZE) {}

int HashTable::hash(const std::string& key) const {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

void HashTable::insert(Music* m) {
    int idx = hash(m->name);
    table[idx].push_back(m);
}

Music* HashTable::search(const std::string& name) {
    int idx = hash(name);
    for (Music* m : table[idx]) {
        if (m->name == name)
            return m;
    }
    return nullptr;
}
