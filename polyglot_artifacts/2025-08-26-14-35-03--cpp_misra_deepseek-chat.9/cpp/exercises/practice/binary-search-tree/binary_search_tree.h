#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <stack>
#include <stdexcept>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(T value) {
        insert_helper(root, value);
    }
    
    bool contains(T value) const {
        return contains_helper(root, value);
    }
    
    const T& data() const {
        if (!root) {
            throw std::runtime_error("Tree is empty");
        }
        return root->data;
    }
    
    binary_tree left() const {
        binary_tree result;
        if (root && root->left) {
            result.root = copy_tree(root->left);
        }
        return result;
    }
    
    binary_tree right() const {
        binary_tree result;
        if (root && root->right) {
            result.root = copy_tree(root->right);
        }
        return result;
    }
    
    
private:
    struct TreeNode {
        T data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        
        explicit TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    
    void insert_helper(std::unique_ptr<TreeNode>& node, T value) {
        if (!node) {
            node = std::make_unique<TreeNode>(value);
        } else if ((value <= node->data)) {
            insert_helper(node->left, value);
        } else {
            insert_helper(node->right, value);
        }
    }
    
    // Helper function to recursively copy a subtree
    std::unique_ptr<TreeNode> copy_tree(const std::unique_ptr<TreeNode>& source) const {
        if (!source) {
            return nullptr;
        }
        auto new_node = std::make_unique<TreeNode>(source->data);
        new_node->left = copy_tree(source->left);
        new_node->right = copy_tree(source->right);
        return new_node;
    }
    
    bool contains_helper(const std::unique_ptr<TreeNode>& node, T value) const {
        if (!node) {
            return false;
        }
        if ((value == node->data)) {
            return true;
        } else if ((value <= node->data)) {
            return contains_helper(node->left, value);
        } else {
            return contains_helper(node->right, value);
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
