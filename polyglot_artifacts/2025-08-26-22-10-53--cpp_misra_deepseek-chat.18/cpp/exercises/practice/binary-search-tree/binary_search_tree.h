#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(const T& data);
    bool contains(const T& data) const;
    
    const T& data() const {
        if (!root) {
            throw std::runtime_error("Accessing data of empty tree");
        }
        return root->data;
    }
    std::unique_ptr<binary_tree<T>> left() const {
        if (!root || !root->left) return nullptr;
        auto left_tree = std::make_unique<binary_tree<T>>();
        left_tree->root = copy_tree(root->left);
        return left_tree;
    }
    std::unique_ptr<binary_tree<T>> right() const {
        if (!root || !root->right) return nullptr;
        auto right_tree = std::make_unique<binary_tree<T>>();
        right_tree->root = copy_tree(root->right);
        return right_tree;
    }

    // Iterator support
    class iterator {
        friend class binary_tree<T>;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(TreeNode* node) : current(nullptr) {
            // Push nodes to the stack to get to the first element (leftmost node)
            while (node) {
                node_stack.push(node);
                node = node->left.get();
            }
            // Set current to the first node (top of the stack)
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            }
        }
        
        reference operator*() const { 
            return current->data; 
        }
        pointer operator->() const { 
            return &current->data; 
        }
        
        iterator& operator++() {
            // If there's a right child, push its leftmost path
            if (current && current->right) {
                TreeNode* temp = current->right.get();
                while (temp) {
                    node_stack.push(temp);
                    temp = temp->left.get();
                }
            }
            
            // Get the next node from the stack
            if (node_stack.empty()) {
                current = nullptr;
            } else {
                current = node_stack.top();
                node_stack.pop();
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        
    private:
        std::stack<TreeNode*> node_stack;
        TreeNode* current;
    };
    
    iterator begin() const {
        return iterator(root.get());
    }
    
    iterator end() const {
        return iterator();
    }

private:
    struct TreeNode {
        T data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        TreeNode(const T& data) : data(data), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    
    // Helper functions
    void insert_helper(std::unique_ptr<TreeNode>& node, const T& data);
    bool contains_helper(const std::unique_ptr<TreeNode>& node, const T& data) const;
    
    // Helper to deep copy a tree
    std::unique_ptr<TreeNode> copy_tree(const std::unique_ptr<TreeNode>& node) const {
        if (!node) return nullptr;
        auto new_node = std::make_unique<TreeNode>(node->data);
        new_node->left = copy_tree(node->left);
        new_node->right = copy_tree(node->right);
        return new_node;
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
