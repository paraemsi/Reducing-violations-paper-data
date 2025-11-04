#include "binary_search_tree.h"
#include <stdexcept>
#include <algorithm>

namespace binary_search_tree {

template<typename T>
binary_tree<T>::binary_tree(const binary_tree& other) {
    root = copy_tree(other.root);
}

template<typename T>
binary_tree<T>& binary_tree<T>::operator=(const binary_tree& other) {
    if (this != &other) {
        destroy_tree(root);
        root = copy_tree(other.root);
    }
    return *this;
}

template<typename T>
binary_tree<T>::~binary_tree() {
    destroy_tree(root);
}

template<typename T>
typename binary_tree<T>::Node* binary_tree<T>::copy_tree(Node* other_node) {
    if (other_node == nullptr) {
        return nullptr;
    }
    Node* new_node = new Node(other_node->data);
    new_node->left = copy_tree(other_node->left);
    new_node->right = copy_tree(other_node->right);
    return new_node;
}

template<typename T>
void binary_tree<T>::destroy_tree(Node* node) {
    if (node != nullptr) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

template<typename T>
void binary_tree<T>::insert(T value) {
    root = insert(root, value);
}

template<typename T>
typename binary_tree<T>::Node* binary_tree<T>::insert(Node* node, T value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value <= node->data) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
    return node;
}

template<typename T>
bool binary_tree<T>::find(T value) const {
    return find(root, value);
}

template<typename T>
bool binary_tree<T>::find(Node* node, T value) const {
    if (node == nullptr) {
        return false;
    }
    if (value == node->data) {
        return true;
    } else if (value < node->data) {
        return find(node->left, value);
    } else {
        return find(node->right, value);
    }
}

template<typename T>
T binary_tree<T>::data() const {
    // Always return the data, even if the tree is empty
    // But according to the tests, the tree should never be empty when data() is called
    // So we can keep the check
    if (root == nullptr) {
        throw std::domain_error("Tree is empty");
    }
    return root->data;
}

template<typename T>
binary_tree<T>* binary_tree<T>::left() const {
    // Always return a new binary_tree with a deep copy of the left subtree
    // If root is nullptr or left is nullptr, the new tree will be empty
    binary_tree<T>* left_tree = new binary_tree<T>();
    if (root) {
        left_tree->root = copy_tree(root->left);
    }
    return left_tree;
}

template<typename T>
binary_tree<T>* binary_tree<T>::right() const {
    // Always return a new binary_tree with a deep copy of the right subtree
    // If root is nullptr or right is nullptr, the new tree will be empty
    binary_tree<T>* right_tree = new binary_tree<T>();
    if (root) {
        right_tree->root = copy_tree(root->right);
    }
    return right_tree;
}

template<typename T>
binary_tree<T>::operator bool() const {
    return root != nullptr;
}

// Explicit instantiations
template class binary_tree<int>;
template class binary_tree<unsigned int>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
