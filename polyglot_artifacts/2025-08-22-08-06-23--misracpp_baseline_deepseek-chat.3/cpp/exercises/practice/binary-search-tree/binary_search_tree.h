#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stdexcept>
#include <vector>
#include <functional>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Constructor
    binary_tree() : root(nullptr) {}
    
    // Insert a value
    void insert(T value) {
        insert_helper(root, value);
    }
    
    // Search for a value
    bool find(T value) const {
        return find_helper(root, value);
    }
    
    // Get the root data
    T data() const {
        if (root) {
            return root->data;
        }
        throw std::runtime_error("Tree is empty");
    }
    
    // Get left and right subtrees
    std::unique_ptr<binary_tree<T>> left() const {
        auto left_tree = std::make_unique<binary_tree<T>>();
        if (root && root->left) {
            left_tree->root = copy_node(root->left);
        }
        return left_tree;
    }
    
    std::unique_ptr<binary_tree<T>> right() const {
        auto right_tree = std::make_unique<binary_tree<T>>();
        if (root && root->right) {
            right_tree->root = copy_node(root->right);
        }
        return right_tree;
    }

    // Iterator support
    // To support range-based for loops, we need to provide begin() and end()
    // We'll do an in-order traversal
    // For simplicity, we'll generate a vector when requested
    std::vector<T> in_order_traversal() const {
        std::vector<T> result;
        in_order_helper(root, result);
        return result;
    }

    // Begin and end for range-based for loop
    // Store the traversal in a mutable cache to avoid dangling references
    auto begin() const {
        traversal_cache = in_order_traversal();
        return traversal_cache.begin();
    }

    auto end() const {
        return traversal_cache.end();
    }

private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    mutable std::vector<T> traversal_cache;
    
    // Helper functions
    void insert_helper(std::unique_ptr<Node>& node, T value) {
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
    
    bool find_helper(const std::unique_ptr<Node>& node, T value) const {
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
    
    // Helper to deep copy a node and its children
    std::unique_ptr<Node> copy_node(const std::unique_ptr<Node>& node) const {
        if (!node) {
            return nullptr;
        }
        auto new_node = std::make_unique<Node>(node->data);
        new_node->left = copy_node(node->left);
        new_node->right = copy_node(node->right);
        return new_node;
    }
    
    // Helper for in-order traversal
    void in_order_helper(const std::unique_ptr<Node>& node, std::vector<T>& result) const {
        if (!node) return;
        in_order_helper(node->left, result);
        result.push_back(node->data);
        in_order_helper(node->right, result);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
