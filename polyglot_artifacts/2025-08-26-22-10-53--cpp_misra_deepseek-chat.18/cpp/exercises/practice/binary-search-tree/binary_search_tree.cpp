#include "binary_search_tree.h"
#include <memory>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(const T& data) {
    insert_helper(root, data);
}

template <typename T>
bool binary_tree<T>::contains(const T& data) const {
    return contains_helper(root, data);
}

template <typename T>
void binary_tree<T>::insert_helper(std::unique_ptr<TreeNode>& node, const T& data) {
    if (!node) {
        node = std::make_unique<TreeNode>(data);
        return;
    }
    
    if (data <= node->data) {
        insert_helper(node->left, data);
    } else {
        insert_helper(node->right, data);
    }
}

template <typename T>
bool binary_tree<T>::contains_helper(const std::unique_ptr<TreeNode>& node, const T& data) const {
    if (!node) {
        return false;
    }
    
    if (node->data == data) {
        return true;
    } else if (data < node->data) {
        return contains_helper(node->left, data);
    } else {
        return contains_helper(node->right, data);
    }
}

// Explicit template instantiation for common types
// This ensures the implementation is available at link time
template class binary_tree<int>;
// Add other types if necessary

}  // namespace binary_search_tree
