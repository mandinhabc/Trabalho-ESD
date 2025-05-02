#include "avltree.hpp"
#include <iostream>
#include <algorithm>

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

AVLNode* AVLTree::insert(AVLNode* node, const Music& m) {
    if (!node)
        return new AVLNode(m);

    if (m.popularity < node->data.popularity)
        node->left = insert(node->left, m);
    else if (m.popularity > node->data.popularity)
        node->right = insert(node->right, m);
    else
        return node;  // ignorar duplicatas de popularidade

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Casos de rotação
    if (balance > 1 && m.popularity < node->left->data.popularity)
        return rightRotate(node);

    if (balance < -1 && m.popularity > node->right->data.popularity)
        return leftRotate(node);

    if (balance > 1 && m.popularity > node->left->data.popularity) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && m.popularity < node->right->data.popularity) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Music& m) {
    root = insert(root, m);
}

Music* AVLTree::search(AVLNode* node, int popularity) {
    if (!node) return nullptr;

    if (popularity == node->data.popularity)
        return &node->data;
    else if (popularity < node->data.popularity)
        return search(node->left, popularity);
    else
        return search(node->right, popularity);
}

Music* AVLTree::search(int popularity) {
    return search(root, popularity);
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
