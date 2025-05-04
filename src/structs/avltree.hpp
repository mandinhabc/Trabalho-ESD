
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "../parser.hpp"
#include <sstream>


struct AVLNode {
    Music data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Music& m);
};

class AVLTree {
private:
    AVLNode* root;

    AVLNode* insert(AVLNode* node, const Music& m);
    Music* search(AVLNode* node, const Music& m);
    void inOrderPrint(AVLNode* node);
    void clear(AVLNode* node);
    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

public:
    AVLTree();
    ~AVLTree();

    void insert(const Music& m);
    Music* search(const Music& m);
    void printInOrder();
};

#endif
