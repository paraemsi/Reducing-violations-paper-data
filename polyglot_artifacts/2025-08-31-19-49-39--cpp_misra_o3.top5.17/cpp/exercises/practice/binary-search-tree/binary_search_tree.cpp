#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::destroy_subtree(BinarySearchTree::Node* node) noexcept {
    if (node != nullptr) {
        destroy_subtree(node->left);
        destroy_subtree(node->right);
        delete node;
    }
}

BinarySearchTree::~BinarySearchTree() noexcept {
    destroy_subtree(root_);
}

BinarySearchTree::Node* BinarySearchTree::insert_node(BinarySearchTree::Node* node, std::int32_t value) {
    if (node == nullptr) {
        return new BinarySearchTree::Node(value);
    }

    if (value <= node->data) {
        node->left = insert_node(node->left, value);
    } else {
        node->right = insert_node(node->right, value);
    }

    return node;
}

bool BinarySearchTree::contains_node(const BinarySearchTree::Node* node, std::int32_t value) {
    if (node == nullptr) {
        return false;
    }

    if (value == node->data) {
        return true;
    }

    if (value < node->data) {
        return contains_node(node->left, value);
    }

    return contains_node(node->right, value);
}

void BinarySearchTree::insert(std::int32_t value) {
    root_ = insert_node(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const {
    return contains_node(root_, value);
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root_(other.root_) {
    other.root_ = nullptr;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        destroy_subtree(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

}  // namespace binary_search_tree
