#include "binary_search_tree.h"

namespace binary_search_tree {

BinarySearchTree::~BinarySearchTree() {
    destroy(root_);
    root_ = nullptr;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept : root_(other.root_) {
    other.root_ = nullptr;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        destroy(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

void BinarySearchTree::insert(int value) {
    root_ = insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return contains(root_, value);
}

// ---------- private helpers ----------

BinarySearchTree::Node* BinarySearchTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value <= node->value) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
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

}  // namespace binary_search_tree
