#include "binary_search_tree.h"
#include <stdexcept>
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(const T& value) {
    insert(root, value);
}

template <typename T>
void binary_tree<T>::insert(Node*& node, const T& value) {
    if (node == nullptr) {
        node = new Node(value);
    } else if (value <= node->data) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

template <typename T>
bool binary_tree<T>::contains(const T& value) const {
    return contains(root, value);
}

template <typename T>
bool binary_tree<T>::contains(Node* node, const T& value) const {
    if (node == nullptr) {
        return false;
    } else if (value == node->data) {
        return true;
    } else if (value < node->data) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    }
}

template <typename T>
const T& binary_tree<T>::data() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    return root->data;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::left() const {
    auto leftTree = std::make_unique<binary_tree<T>>();
    if (root != nullptr) {
        leftTree->root = root->left;
    }
    return leftTree;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::right() const {
    auto rightTree = std::make_unique<binary_tree<T>>();
    if (root != nullptr) {
        rightTree->root = root->right;
    }
    return rightTree;
}

template <typename T>
void binary_tree<T>::in_order_traversal(Node* node, std::vector<T>& result) const {
    if (node == nullptr) return;
    in_order_traversal(node->left, result);
    result.push_back(node->data);
    in_order_traversal(node->right, result);
}

template <typename T>
typename std::vector<T>::const_iterator binary_tree<T>::begin() const {
    static std::vector<T> elements;
    elements.clear();
    in_order_traversal(root, elements);
    return elements.begin();
}

template <typename T>
typename std::vector<T>::const_iterator binary_tree<T>::end() const {
    static std::vector<T> elements;
    elements.clear();
    in_order_traversal(root, elements);
    return elements.end();
}

// Explicit instantiation for int to satisfy potential linker errors
template class binary_tree<int>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
