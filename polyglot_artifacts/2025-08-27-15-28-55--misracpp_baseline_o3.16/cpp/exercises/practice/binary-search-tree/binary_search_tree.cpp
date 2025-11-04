#include "binary_search_tree.h"

#include <cstddef>

namespace binary_search_tree {

// -------------------- Node definition --------------------
struct BinarySearchTree::Node {
    int   data;
    Node* left;
    Node* right;

    explicit Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

// -------------------- Public interface --------------------
BinarySearchTree::BinarySearchTree() : root_(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroy(root_);
}

void BinarySearchTree::insert(int value) {
    root_ = insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return contains(root_, value);
}

// -------------------- Private helpers --------------------
BinarySearchTree::Node* BinarySearchTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }

    if (value <= node->data) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
    return node;
}

bool BinarySearchTree::contains(Node* node, int value) const {
    if (node == nullptr) {
        return false;
    }
    if (value == node->data) {
        return true;
    }
    if (value < node->data) {
        return contains(node->left, value);
    }
    return contains(node->right, value);
}

void BinarySearchTree::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

}  // namespace binary_search_tree
