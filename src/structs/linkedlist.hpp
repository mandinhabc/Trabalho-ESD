#ifndef C0694388_E81D_42AE_9D6F_7ADA869CE8FD
#define C0694388_E81D_42AE_9D6F_7ADA869CE8FD


#endif /* C0694388_E81D_42AE_9D6F_7ADA869CE8FD */
#pragma once
#include "../parser.hpp"
#include <string>

struct Node {
    Music data;
    Node* next;

    Node(const Music& m) : data(m), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insert(const Music& m);
    bool remove_by_id(const std::string& id);
    Music* find_by_name(const std::string& name);
    void print_sample(int n) const;
};
