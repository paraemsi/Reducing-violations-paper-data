#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>
#include <stdexcept>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(T value) {
        insert_impl(root, value);
    }
    
    bool contains(T value) const {
        return contains_impl(root.get(), value);
    }
    
    const T& data() const {
        // Add a check to prevent undefined behavior
        // If the tests call data() on an empty tree, this will throw
        if (!root) {
            throw std::runtime_error("Data called on empty tree");
        }
        return root->data;
    }
    
    const binary_tree* left() const {
        if (root && root->left) {
            // Create a new binary_tree that doesn't take ownership of the node
            // We'll use a custom deleter that does nothing to avoid double deletion
            binary_tree* left_tree = new binary_tree();
            left_tree->root = std::unique_ptr<TreeNode>(const_cast<TreeNode*>(root->left.get()), [](TreeNode*){});
            return left_tree;
        }
        return nullptr;
    }
    
    const binary_tree* right() const {
        if (root && root->right) {
            binary_tree* right_tree = new binary_tree();
            right_tree->root = std::unique_ptr<TreeNode>(const_cast<TreeNode*>(root->right.get()), [](TreeNode*){});
            return right_tree;
        }
        return nullptr;
    }
    
    // Iterator support
    // To support range-based for loops, we need begin() and end()
    // We'll do an in-order traversal
    std::vector<T> in_order() const {
        std::vector<T> result;
        in_order_impl(root.get(), result);
        return result;
    }
    
    // For iterator support
    auto begin() const {
        auto elements = in_order();
        return elements.begin();
    }
    
    auto end() const {
        auto elements = in_order();
        return elements.end();
    }

private:
    struct TreeNode {
        T data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        
        explicit TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    
    void insert_impl(std::unique_ptr<TreeNode>& node, T value) {
        if (!node) {
            node = std::make_unique<TreeNode>(value);
            return;
        }
        
        if (value <= node->data) {
            insert_impl(node->left, value);
        } else {
            insert_impl(node->right, value);
        }
    }
    
    bool contains_impl(const TreeNode* node, T value) const {
        if (!node) {
            return false;
        }
        
        if (node->data == value) {
            return true;
        }
        
        if (value <= node->data) {
            return contains_impl(node->left.get(), value);
        } else {
            return contains_impl(node->right.get(), value);
        }
    }
    
    void in_order_impl(const TreeNode* node, std::vector<T>& result) const {
        if (!node) return;
        in_order_impl(node->left.get(), result);
        result.push_back(node->data);
        in_order_impl(node->right.get(), result);
    }
};

// Helper function to make a tree from a list of values
template<typename T>
binary_tree<T> make_tree(const std::vector<T>& values) {
    binary_tree<T> tree;
    for (const auto& value : values) {
        tree.insert(value);
    }
    return tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
