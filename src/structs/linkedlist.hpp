
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "../parser.hpp"
#include <string>
#include <sstream>

struct Node {
    Music* data;  // Ponteiro para evitar cópias grandes
    Node* next;

    Node(Music* m);
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insert(Music* m); // Usa ponteiro ao invés de cópia
    bool remove_by_id(const std::string& id);
    Music* find_by_name(const std::string& name);
    void print_sample(int n) const;
};

#endif
