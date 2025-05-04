
#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "../parser.hpp"
#include <vector>
#include <list>
#include <sstream>

class HashTable {
private:
    static const int TABLE_SIZE = 1031;  // Número primo para reduzir colisões
    std::vector<std::list<Music*>> table;

    int hash(const std::string& key) const;

public:
    HashTable();
    void insert(Music* m);
    Music* search(const std::string& name);
};

#endif
