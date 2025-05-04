#include "avltree.hpp"
#include <iostream>
#include <algorithm>


AVLNode::AVLNode(const Music& m) : data(m), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear(root);
}

void AVLTree::clear(AVLNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

bool compareMusic(const Music& m1, const Music& m2) {
    if (m1.popularity != m2.popularity)
        return m1.popularity < m2.popularity;
    return m1.name < m2.name;
}

AVLNode* AVLTree::insert(AVLNode* node, const Music& m) {
    if (!node)
        return new AVLNode(m);

    if (compareMusic(m, node->data))
        node->left = insert(node->left, m);
    else if (compareMusic(node->data, m))
        node->right = insert(node->right, m);
    else
        return node;  // música já existente

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && compareMusic(m, node->left->data))
        return rightRotate(node);

    if (balance < -1 && compareMusic(node->right->data, m))
        return leftRotate(node);

    if (balance > 1 && compareMusic(node->left->data, m)) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && compareMusic(m, node->right->data)) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Music& m) {
    root = insert(root, m);
}

Music* AVLTree::search(AVLNode* node, const Music& m) {
    if (!node)
        return nullptr;

    if (m.popularity == node->data.popularity && m.name == node->data.name)
        return &node->data;
    else if (compareMusic(m, node->data))
        return search(node->left, m);
    else
        return search(node->right, m);
}

Music* AVLTree::search(const Music& m) {
    return search(root, m);
}

void AVLTree::inOrderPrint(AVLNode* node) {
    if (node) {
        inOrderPrint(node->left);
        std::cout << node->data.name << " (" << node->data.popularity << ")\n";
        inOrderPrint(node->right);
    }
}

void AVLTree::printInOrder() {
    inOrderPrint(root);
}
