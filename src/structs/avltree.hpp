#ifndef A725B2CD_8C76_429B_B2AA_8C90ED954911
#define A725B2CD_8C76_429B_B2AA_8C90ED954911


#endif /* A725B2CD_8C76_429B_B2AA_8C90ED954911 */
#pragma once
#include "../parser.hpp"

struct AVLNode {
    Music data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Music& m) : data(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const Music& m);
    void inOrderPrint(AVLNode* node);
    Music* search(AVLNode* node, int popularity);

public:
    AVLTree();
    ~AVLTree();
    void insert(const Music& m);
    Music* search(int popularity);
    void printInOrder();  // Para debug: exibe em ordem crescente de popularidade
    void clear(AVLNode* node);  // Destrutor
};
