#include "binary_search_tree.h"
#include <memory>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(T value) {
    insert_helper(root, value);
}

template <typename T>
bool binary_tree<T>::find(T value) const {
    return find_helper(root, value);
}

template <typename T>
T binary_tree<T>::data() const {
    if (root) {
        return root->data;
    }
    // Return default value if the tree is empty
    return T();
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
void binary_tree<T>::insert_helper(std::unique_ptr<Node>& node, T value) {
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
bool binary_tree<T>::find_helper(const std::unique_ptr<Node>& node, T value) const {
    if (!node) {
        return false;
    }
    if (node->data == value) {
        return true;
    }
    if (value < node->data) {
        return find_helper(node->left, value);
    } else {
        return find_helper(node->right, value);
    }
}

template <typename T>
std::vector<T> binary_tree<T>::get_elements_in_order() const {
    std::vector<T> result;
    in_order_traversal_helper(root, result);
    return result;
}

template <typename T>
void binary_tree<T>::in_order_traversal_helper(const std::unique_ptr<Node>& node, std::vector<T>& result) const {
    if (!node) {
        return;
    }
    in_order_traversal_helper(node->left, result);
    result.push_back(node->data);
    in_order_traversal_helper(node->right, result);
}

// Explicit instantiation for int type
template class binary_tree<int>;
// Also instantiate for std::string to support string tests
template class binary_tree<std::string>;

}  // namespace binary_search_tree
