#include "binary_search_tree.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace binary_search_tree {

// Insert implementation
template <typename T>
void binary_tree<T>::insert(const T& value) {
    insert_helper(root, value);
}

template <typename T>
void binary_tree<T>::insert_helper(std::unique_ptr<Node>& node, const T& value) {
    if (!node) {
        node = std::make_unique<Node>(value);
    } else if (value <= node->data) {
        insert_helper(node->left, value);
    } else {
        insert_helper(node->right, value);
    }
}

// Contains implementation
template <typename T>
bool binary_tree<T>::contains(const T& value) const {
    return contains_helper(root, value);
}

template <typename T>
bool binary_tree<T>::contains_helper(const std::unique_ptr<Node>& node, const T& value) const {
    if (!node) {
        return false;
    }
    if (node->data == value) {
        return true;
    } else if (value < node->data) {
        return contains_helper(node->left, value);
    } else {
        return contains_helper(node->right, value);
    }
}

// Data implementation
template <typename T>
const T& binary_tree<T>::data() const {
    if (!root) {
        throw std::domain_error("Tree is empty");
    }
    return root->data;
}

// Helper function to deep copy a node and its children
template <typename T>
std::unique_ptr<typename binary_tree<T>::Node> binary_tree<T>::copy_tree(const std::unique_ptr<Node>& node) {
    if (!node) {
        return nullptr;
    }
    auto new_node = std::make_unique<Node>(node->data);
    new_node->left = copy_tree(node->left);
    new_node->right = copy_tree(node->right);
    return new_node;
}

// Left implementation
template <typename T>
binary_tree<T>* binary_tree<T>::left() const {
    if (!root || !root->left) {
        return nullptr;
    }
    // Create a new tree and set its root to a deep copy of the left subtree
    auto* left_tree = new binary_tree<T>();
    left_tree->root = copy_tree(root->left);
    return left_tree;
}

// Right implementation
template <typename T>
binary_tree<T>* binary_tree<T>::right() const {
    if (!root || !root->right) {
        return nullptr;
    }
    // Create a new tree and set its root to a deep copy of the right subtree
    auto* right_tree = new binary_tree<T>();
    right_tree->root = copy_tree(root->right);
    return right_tree;
}

// Explicit instantiation for required types
template class binary_tree<int>;
template class binary_tree<uint32_t>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
