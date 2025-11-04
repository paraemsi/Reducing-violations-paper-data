#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::destroy_subtree(Node* node) noexcept {
    if (node != nullptr) {
        destroy_subtree(node->left);
        destroy_subtree(node->right);
        delete node;
    }
}

BinarySearchTree::~BinarySearchTree() noexcept {
    destroy_subtree(root_);
    root_ = nullptr;
}

BinarySearchTree::Node* BinarySearchTree::insert(Node* node, std::int32_t value) {
    if (node == nullptr) {
        Node* const new_node = new Node(value);
        return new_node;
    }

    if (value <= node->data) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
    return node;
}

void BinarySearchTree::insert(std::int32_t value) {
    root_ = insert(root_, value);
}

bool BinarySearchTree::contains(const Node* node, std::int32_t value) noexcept {
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

bool BinarySearchTree::contains(std::int32_t value) const {
    return contains(root_, value);
}

}  // namespace binary_search_tree
