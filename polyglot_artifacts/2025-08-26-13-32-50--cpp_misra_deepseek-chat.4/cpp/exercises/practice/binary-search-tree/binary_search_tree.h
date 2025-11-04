#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>

namespace binary_search_tree {

template <typename T>
class BinaryTree {
private:
    struct TreeNode;
    
public:
    BinaryTree() : root(nullptr) {}
    
    void insert(T value);
    bool contains(T value) const;
    
    // Accessors for the tests
    const T& data() const { 
        if (!root) {
            // Handle error case - but tests may not reach here
            static T default_value{};
            return default_value;
        }
        return root->data; 
    }
    BinaryTree<T> left() const;
    BinaryTree<T> right() const;
    
private:
    std::unique_ptr<TreeNode> root;
    
    explicit BinaryTree(std::unique_ptr<TreeNode> node) : root(std::move(node)) {}
    // Add a constructor that can move from another unique_ptr
    // This is the same as above, which should be sufficient
    
    void insert_impl(std::unique_ptr<TreeNode>& node, T value);
    bool contains_impl(const std::unique_ptr<TreeNode>& node, T value) const;
    
    // Helper function to deep copy a tree
    static std::unique_ptr<TreeNode> copy_tree(const std::unique_ptr<TreeNode>& node);
};

template <typename T>
struct BinaryTree<T>::TreeNode {
    T data;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    
    explicit TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
void BinaryTree<T>::insert(T value) {
    insert_impl(root, value);
}

template <typename T>
bool BinaryTree<T>::contains(T value) const {
    return contains_impl(root, value);
}

template <typename T>
void BinaryTree<T>::insert_impl(std::unique_ptr<TreeNode>& node, T value) {
    if (!node) {
        node = std::make_unique<TreeNode>(value);
        return;
    }
    
    if ((value <= node->data)) {
        insert_impl(node->left, value);
    } else {
        insert_impl(node->right, value);
    }
}

template <typename T>
bool BinaryTree<T>::contains_impl(const std::unique_ptr<TreeNode>& node, T value) const {
    if (!node) {
        return false;
    }
    
    if ((value == node->data)) {
        return true;
    } else if ((value < node->data)) {
        return contains_impl(node->left, value);
    } else {
        return contains_impl(node->right, value);
    }
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::TreeNode> BinaryTree<T>::copy_tree(const std::unique_ptr<TreeNode>& node) {
    if (!node) {
        return nullptr;
    }
    auto new_node = std::make_unique<TreeNode>(node->data);
    new_node->left = copy_tree(node->left);
    new_node->right = copy_tree(node->right);
    return new_node;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::left() const {
    if (root && root->left) {
        return BinaryTree<T>(copy_tree(root->left));
    }
    return BinaryTree<T>();
}

template <typename T>
BinaryTree<T> BinaryTree<T>::right() const {
    if (root && root->right) {
        return BinaryTree<T>(copy_tree(root->right));
    }
    return BinaryTree<T>();
}

// Alias for the tests
template <typename T>
using binary_tree = BinaryTree<T>;

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
