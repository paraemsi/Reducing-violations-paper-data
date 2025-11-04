#include "binary_search_tree.h"

namespace binary_search_tree {

// Public interface ---------------------------------------------------------

void BinarySearchTree::insert(int value) {
    root_ = insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return contains(root_, value);
}

BinarySearchTree::~BinarySearchTree() {
    destroy(root_);
}

// Copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
    : root_(clone(other.root_)) {}

// Copy assignment
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this != &other) {
        destroy(root_);
        root_ = clone(other.root_);
    }
    return *this;
}

// Move constructor
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root_(other.root_) {
    other.root_ = nullptr;
}

// Move assignment
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        destroy(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

// Private helpers ----------------------------------------------------------

BinarySearchTree::Node* BinarySearchTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }

    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    }
    // Duplicate values are ignored (no insertion)

    return node;
}

bool BinarySearchTree::contains(const Node* node, int value) {
    if (node == nullptr) {
        return false;
    }
    if (value == node->value) {
        return true;
    }
    if (value < node->value) {
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

// Deep-copy helper
BinarySearchTree::Node* BinarySearchTree::clone(const Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    Node* new_node = new Node(node->value);
    new_node->left  = clone(node->left);
    new_node->right = clone(node->right);
    return new_node;
}

}  // namespace binary_search_tree
