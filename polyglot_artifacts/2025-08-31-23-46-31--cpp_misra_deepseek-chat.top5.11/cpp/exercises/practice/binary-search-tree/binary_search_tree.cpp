#include "binary_search_tree.h"
#include <stdexcept>
#include <vector>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(T value) {
    insert_impl(root, value);
}

template <typename T>
void binary_tree<T>::insert_impl(std::unique_ptr<Node>& node, T value) {
    if (!node) {
        node = std::make_unique<Node>(value);
    } else {
        if ((value <= node->data)) {
            insert_impl(node->left, value);
        } else {
            insert_impl(node->right, value);
        }
    }
}

template <typename T>
bool binary_tree<T>::contains(T value) const {
    return contains_impl(root, value);
}

template <typename T>
bool binary_tree<T>::contains_impl(const std::unique_ptr<Node>& node, T value) const {
    if (!node) {
        return false;
    }
    if (value == node->data) {
        return true;
    } else {
        if ((value < node->data)) {
            return contains_impl(node->left, value);
        } else {
            return contains_impl(node->right, value);
        }
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
std::unique_ptr<typename binary_tree<T>::Node> binary_tree<T>::copy_node(const std::unique_ptr<Node>& node) {
    if (!node) {
        return nullptr;
    }
    auto new_node = std::make_unique<Node>(node->data);
    new_node->left = copy_node(node->left);
    new_node->right = copy_node(node->right);
    return new_node;
}

template <typename T>
const binary_tree<T>* binary_tree<T>::left() const {
    if (root && root->left) {
        binary_tree<T>* leftTree = new binary_tree<T>();
        leftTree->root = copy_node(root->left);
        return leftTree;
    } else {
        return nullptr;
    }
}

template <typename T>
const binary_tree<T>* binary_tree<T>::right() const {
    if (root && root->right) {
        binary_tree<T>* rightTree = new binary_tree<T>();
        rightTree->root = copy_node(root->right);
        return rightTree;
    } else {
        return nullptr;
    }
}

// Also instantiate for std::string since the tests use it
#include <string>
// Explicit instantiations to satisfy the linker
template class binary_tree<int>;
template class binary_tree<std::string>;

// Iterator implementation
template <typename T>
void binary_tree<T>::iterator::push_left(Node* node) {
    while (node) {
        stack.push_back(node);
        node = node->left.get();
    }
}

template <typename T>
binary_tree<T>::iterator::iterator(Node* root) {
    push_left(root);
    if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
    } else {
        current = nullptr;
    }
}

template <typename T>
typename binary_tree<T>::iterator::reference binary_tree<T>::iterator::operator*() const {
    return current->data;
}

template <typename T>
typename binary_tree<T>::iterator::pointer binary_tree<T>::iterator::operator->() const {
    return &current->data;
}

template <typename T>
typename binary_tree<T>::iterator& binary_tree<T>::iterator::operator++() {
    if (current->right) {
        push_left(current->right.get());
    }
    if (stack.empty()) {
        current = nullptr;
    } else {
        current = stack.back();
        stack.pop_back();
    }
    return *this;
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
bool binary_tree<T>::iterator::operator==(const iterator& other) const {
    return current == other.current;
}

template <typename T>
bool binary_tree<T>::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::begin() const {
    return iterator(root.get());
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::end() const {
    return iterator(nullptr);
}

}  // namespace binary_search_tree
