#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <stdexcept>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    explicit binary_tree(T data) : root(std::make_unique<TreeNode>(data)) {}
    
    void insert(T value) {
        insert_impl(root, value);
    }
    
    const T& data() const {
        if (root) {
            return root->data;
        }
        // Handle the case where root is nullptr
        // Since we can't return a reference to nothing, we need to throw or have a static member
        // For now, we'll throw an exception
        throw std::runtime_error("Accessing data of an empty tree");
    }
    
    const binary_tree* left() const {
        if (root && root->left) {
            return reinterpret_cast<const binary_tree*>(root->left.get());
        }
        return nullptr;
    }
    
    const binary_tree* right() const {
        if (root && root->right) {
            return reinterpret_cast<const binary_tree*>(root->right.get());
        }
        return nullptr;
    }
    
    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : current(nullptr) {}
        
        reference operator*() const { 
            return current->data(); 
        }
        
        pointer operator->() const { 
            return &current->data(); 
        }
        
        iterator& operator++() {
            if (stack.empty()) {
                current = nullptr;
            } else {
                current = stack.back();
                stack.pop_back();
                // Push all left children of the right subtree
                push_left(current->right());
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
            return current != other.current; 
        }
        
    private:
        const binary_tree* current;
        std::vector<const binary_tree*> stack;
        
        void push_left(const binary_tree* node) {
            while (node) {
                stack.push_back(node);
                node = node->left();
            }
        }
        
        explicit iterator(const binary_tree* node) : current(nullptr) {
            if (node) {
                // Push the root and all left children
                push_left(node);
                // The first element is at the top of the stack
                if (!stack.empty()) {
                    current = stack.back();
                    stack.pop_back();
                    // Push all left children of the right subtree
                    push_left(current->right());
                }
            }
        }
        
        friend class binary_tree;
    };
    
    iterator begin() const { 
        return iterator(this); 
    }
    
    iterator end() const { 
        return iterator(); 
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
        } else {
            if ((value <= node->data)) {
                insert_impl(node->left, value);
            } else {
                insert_impl(node->right, value);
            }
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
