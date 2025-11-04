#include "binary_search_tree.h"
#include <stdexcept>
#include <string>

namespace binary_search_tree {

template<typename T>
void binary_tree<T>::insert(const T& value) {
    insert(root, value);
}

template<typename T>
void binary_tree<T>::insert(Node*& node, const T& value) {
    if (node == nullptr) {
        node = new Node(value);
    } else if (value <= node->data) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

template<typename T>
T* binary_tree<T>::find(const T& value) const {
    Node* found = find(root, value);
    if (found) {
        return &(found->data);
    }
    return nullptr;
}

template<typename T>
typename binary_tree<T>::Node* binary_tree<T>::find(Node* node, const T& value) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (value == node->data) {
        return node;
    } else if (value < node->data) {
        return find(node->left, value);
    } else {
        return find(node->right, value);
    }
}

template<typename T>
T binary_tree<T>::data() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    return root->data;
}

template<typename T>
binary_tree<T>* binary_tree<T>::left() const {
    if (root == nullptr || root->left == nullptr) {
        return new binary_tree<T>();
    }
    // Create a new tree and deep copy the left subtree
    binary_tree<T>* left_tree = new binary_tree<T>();
    // Helper function to copy the subtree recursively
    auto copyTree = [](Node* source) -> Node* {
        if (source == nullptr) return nullptr;
        Node* new_node = new Node(source->data);
        new_node->left = copyTree(source->left);
        new_node->right = copyTree(source->right);
        return new_node;
    };
    left_tree->root = copyTree(root->left);
    return left_tree;
}

template<typename T>
binary_tree<T>* binary_tree<T>::right() const {
    if (root == nullptr || root->right == nullptr) {
        return new binary_tree<T>();
    }
    // Create a new tree and deep copy the right subtree
    binary_tree<T>* right_tree = new binary_tree<T>();
    // Helper function to copy the subtree recursively
    auto copyTree = [](Node* source) -> Node* {
        if (source == nullptr) return nullptr;
        Node* new_node = new Node(source->data);
        new_node->left = copyTree(source->left);
        new_node->right = copyTree(source->right);
        return new_node;
    };
    right_tree->root = copyTree(root->right);
    return right_tree;
}

template<typename T>
binary_tree<T>::~binary_tree() {
    // Helper function to delete nodes recursively
    auto deleteNode = [](Node* node) {
        if (node) {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    };
    deleteNode(root);
}

// Explicit template instantiation for int and std::string
template class binary_tree<int>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
