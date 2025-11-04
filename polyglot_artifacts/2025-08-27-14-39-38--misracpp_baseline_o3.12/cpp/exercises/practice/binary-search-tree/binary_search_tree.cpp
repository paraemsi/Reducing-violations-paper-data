#include "binary_search_tree.h"
#include <utility>

namespace binary_search_tree {

// ――――――――――――――――――――――――――――――――――――――――――
// Private helper implementations
// ――――――――――――――――――――――――――――――――――――――――――
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

bool BinarySearchTree::contains(const Node* node, int value) {
    if (node == nullptr) {
        return false;
    }

    if (value == node->data) {
        return true;
    }

    return value < node->data
           ? contains(node->left, value)
           : contains(node->right, value);
}

void BinarySearchTree::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

// ――――――――――――――――――――――――――――――――――――――――――
// Public interface implementations
// ――――――――――――――――――――――――――――――――――――――――――
BinarySearchTree::~BinarySearchTree() {
    destroy(root_);
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root_(other.root_) {
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
    insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return BinarySearchTree::contains(root_, value);
}

}  // namespace binary_search_tree
