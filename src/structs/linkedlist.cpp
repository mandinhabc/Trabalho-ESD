#include "linkedlist.hpp"
#include <iostream>
#include <sstream> 

Node::Node(Music* m) : data(m), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp->data;  // libera o Music alocado
        delete temp;
    }
}

void LinkedList::insert(Music* m) {
    Node* new_node = new Node(m);
    if (!head) {
        head = new_node;
    } else {
        Node* current = head;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

bool LinkedList::remove_by_id(const std::string& id) {
    Node* current = head;
    Node* prev = nullptr;

    while (current) {
        if (current->data->id == id) {
            if (prev) prev->next = current->next;
            else head = current->next;

            delete current->data;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

Music* LinkedList::find_by_name(const std::string& name) {
    Node* current = head;
    while (current) {
        if (current->data->name == name)
            return current->data;
        current = current->next;
    }
    return nullptr;
}

void LinkedList::print_sample(int n) const {
    Node* current = head;
    int count = 0;
    while (current && count < n) {
        std::cout << current->data->name << " - " << current->data->artist << std::endl;
        current = current->next;
        count++;
    }
}
