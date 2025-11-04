#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace binary_search_tree {

class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(std::uint32_t value) {
        insert_impl(root, value);
    }
    
    bool contains(std::uint32_t value) const {
        return contains_impl(root, value);
    }
    
    std::uint32_t data() const {
        if (!root) {
            throw std::runtime_error("Accessing data of an empty tree");
        }
        return root->data;
    }
    
    const binary_tree* left() const {
        if (root && root->left) {
            left_tree = std::make_unique<binary_tree>();
            // Collect all values from the left subtree and insert them into left_tree
            std::vector<std::uint32_t> values;
            collect_values(root->left, values);
            for (const auto& val : values) {
                left_tree->insert(val);
            }
            return left_tree.get();
        }
        return nullptr;
    }
    
    const binary_tree* right() const {
        if (root && root->right) {
            right_tree = std::make_unique<binary_tree>();
            // Collect all values from the right subtree and insert them into right_tree
            std::vector<std::uint32_t> values;
            collect_values(root->right, values);
            for (const auto& val : values) {
                right_tree->insert(val);
            }
            return right_tree.get();
        }
        return nullptr;
    }
    
private:
    struct TreeNode {
        std::uint32_t data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        
        explicit TreeNode(std::uint32_t value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    mutable std::unique_ptr<binary_tree> left_tree;
    mutable std::unique_ptr<binary_tree> right_tree;
    
    void insert_impl(std::unique_ptr<TreeNode>& node, std::uint32_t value) {
        if (!node) {
            node = std::make_unique<TreeNode>(value);
        } else if (value <= node->data) {
            insert_impl(node->left, value);
        } else {
            insert_impl(node->right, value);
        }
    }
    
    bool contains_impl(const std::unique_ptr<TreeNode>& node, std::uint32_t value) const {
        if (!node) {
            return false;
        }
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return contains_impl(node->left, value);
        } else {
            return contains_impl(node->right, value);
        }
    }
    
    void collect_values(const std::unique_ptr<TreeNode>& node, std::vector<std::uint32_t>& values) const {
        if (!node) {
            return;
        }
        // In-order traversal to maintain order
        collect_values(node->left, values);
        values.push_back(node->data);
        collect_values(node->right, values);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
