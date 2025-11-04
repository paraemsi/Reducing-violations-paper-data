#include "binary_search_tree.h"

namespace binary_search_tree {

BinarySearchTree::~BinarySearchTree() {
    clear(root_);
    root_ = nullptr;
}

// Copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : root_(nullptr) {
    root_ = clone(other.root_);
}

// Copy assignment operator
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this == &other) {
        return *this;
    }
    clear(root_);
    root_ = clone(other.root_);
    return *this;
}

// Move constructor
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept : root_(other.root_) {
    other.root_ = nullptr;
}

// Move assignment operator
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    clear(root_);
    root_ = other.root_;
    other.root_ = nullptr;
    return *this;
}

void BinarySearchTree::insert(int value) {
    insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return contains(root_, value);
}

// Private helper implementations
void BinarySearchTree::insert(Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return;
    }

    if (value <= node->data) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

bool BinarySearchTree::contains(const Node* node, int value) const {
    if (node == nullptr) {
        return false;
    }
    if (node->data == value) {
        return true;
    }
    if (value < node->data) {
        return contains(node->left, value);
    }
    return contains(node->right, value);
}

void BinarySearchTree::clear(Node* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

Node* BinarySearchTree::clone(const Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    Node* new_node = new Node(node->data);
    new_node->left = clone(node->left);
    new_node->right = clone(node->right);
    return new_node;
}

}  // namespace binary_search_tree
