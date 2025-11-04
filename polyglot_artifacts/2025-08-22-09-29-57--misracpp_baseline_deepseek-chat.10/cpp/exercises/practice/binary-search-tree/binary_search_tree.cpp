#include "binary_search_tree.h"

namespace binary_search_tree {

template <typename T>
TreeNode<T>* binary_tree<T>::insert(TreeNode<T>* node, T value) {
    if (node == nullptr) {
        return new TreeNode<T>(value);
    }
    if (value <= node->data_) {
        node->left_ = insert(node->left_, value);
    } else {
        node->right_ = insert(node->right_, value);
    }
    return node;
}

template <typename T>
void binary_tree<T>::insert(T value) {
    root = insert(root, value);
}

template <typename T>
TreeNode<T>* binary_tree<T>::find(TreeNode<T>* node, T value) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->data_ == value) {
        return node;
    }
    if (value < node->data_) {
        return find(node->left_, value);
    } else {
        return find(node->right_, value);
    }
}

template <typename T>
TreeNode<T>* binary_tree<T>::find(T value) const {
    return find(root, value);
}

// Explicit instantiations for common types
template class TreeNode<int>;
template class TreeNode<unsigned int>;
template class TreeNode<std::string>;

template class binary_tree<int>;
template class binary_tree<unsigned int>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
