#include "binary_search_tree.h"
#include <memory>
#include <stdexcept>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::get_sorted_elements_helper(const std::unique_ptr<Node>& node, std::vector<T>& result) const {
    if (!node) return;
    get_sorted_elements_helper(node->left, result);
    result.push_back(node->data);
    get_sorted_elements_helper(node->right, result);
}

template <typename T>
void binary_tree<T>::insert(const T& value) {
    insert_helper(root, value);
}

template <typename T>
void binary_tree<T>::insert_helper(std::unique_ptr<Node>& node, const T& value) {
    if (!node) {
        node = std::make_unique<Node>(value);
        return;
    }
    if (value <= node->data) {
        insert_helper(node->left, value);
    } else {
        insert_helper(node->right, value);
    }
}

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
    }
    if (value < node->data) {
        return contains_helper(node->left, value);
    } else {
        return contains_helper(node->right, value);
    }
}

template <typename T>
const T& binary_tree<T>::data() const {
    if (!root) {
        throw std::runtime_error("Tree is empty");
    }
    return root->data;
}

template <typename T>
std::unique_ptr<typename binary_tree<T>::Node> binary_tree<T>::copy_node(const std::unique_ptr<Node>& node) const {
    if (!node) {
        return nullptr;
    }
    auto new_node = std::make_unique<Node>(node->data);
    new_node->left = copy_node(node->left);
    new_node->right = copy_node(node->right);
    return new_node;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::left() const {
    auto left_tree = std::make_unique<binary_tree<T>>();
    if (root && root->left) {
        left_tree->root = copy_node(root->left);
    }
    return left_tree;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::right() const {
    auto right_tree = std::make_unique<binary_tree<T>>();
    if (root && root->right) {
        right_tree->root = copy_node(root->right);
    }
    return right_tree;
}

// Explicit instantiation for int to satisfy the linker
template class binary_tree<int>;
// Also for std::string
template class binary_tree<std::string>;

}  // namespace binary_search_tree
