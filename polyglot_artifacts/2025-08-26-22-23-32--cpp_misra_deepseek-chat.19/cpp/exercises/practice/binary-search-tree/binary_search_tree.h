#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <functional>

namespace binary_search_tree {

template<typename T>
struct TreeNode;

template<typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    explicit binary_tree(T data) : root(std::make_unique<TreeNode>(data)) {}
    
    void insert(T value) {
        insert(root, value);
    }
    
    bool contains(T value) const {
        return contains(root, value);
    }
    
    T data() const {
        return root->tree.data();
    }
    
    const binary_tree* left() const {
        if (root && root->left) {
            return &root->left->tree;
        }
        return nullptr;
    }
    
    const binary_tree* right() const {
        if (root && root->right) {
            return &root->right->tree;
        }
        return nullptr;
    }
    
    // Iterator support - the tests may be using range-based for loops
    // Let's provide begin() and end() functions that return iterators to the in-order traversal
    std::vector<T> in_order_traversal() const {
        std::vector<T> result;
        in_order_traversal(root, result);
        return result;
    }
    
    // To support range-based for loops, we need to provide begin() and end()
    auto begin() const {
        std::vector<T> result;
        in_order_traversal(root, result);
        return result.begin();
    }
    
    auto end() const {
        std::vector<T> result;
        in_order_traversal(root, result);
        return result.end();
    }
    
private:
    struct TreeNode {
        binary_tree<T> tree;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        
        explicit TreeNode(T value) : tree(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    
    void insert(std::unique_ptr<TreeNode>& node, T value) {
        if (!node) {
            node = std::make_unique<TreeNode>(value);
            return;
        }
        if ((value <= node->tree.data())) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }
    
    bool contains(const std::unique_ptr<TreeNode>& node, T value) const {
        if (!node) {
            return false;
        }
        if ((value == node->tree.data())) {
            return true;
        } else if ((value < node->tree.data())) {
            return contains(node->left, value);
        } else {
            return contains(node->right, value);
        }
    }
    
    void in_order_traversal(const std::unique_ptr<TreeNode>& node, std::vector<T>& result) const {
        if (!node) return;
        in_order_traversal(node->left, result);
        result.push_back(node->tree.data());
        in_order_traversal(node->right, result);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
