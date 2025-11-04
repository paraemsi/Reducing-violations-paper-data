#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <stack>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    explicit binary_tree(const T& value) : root(std::make_unique<Node>(value)) {}
    
    void insert(T value) {
        insert_impl(root, value);
    }
    
    bool find(T value) const {
        return find_impl(root, value);
    }
    
    const T& data() const {
        if (!root) { 
            throw std::runtime_error("Tree is empty");
        }
        return root->data;
    }
    
    binary_tree left() const {
        if (!root) { 
            throw std::runtime_error("Tree is empty");
        }
        binary_tree left_tree;
        left_tree.root = copy_node(root->left);
        return left_tree;
    }
    
    binary_tree right() const {
        if (!root) { 
            throw std::runtime_error("Tree is empty");
        }
        binary_tree right_tree;
        right_tree.root = copy_node(root->right);
        return right_tree;
    }
    
    // Iterator class for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(Node* root) : current(nullptr) {
            // Push all left nodes to reach the smallest element
            if (root) {
                push_left(root);
                // The first element is at the top of the stack
                if (!node_stack.empty()) {
                    current = node_stack.top();
                    node_stack.pop();
                    // Push the left nodes of the right child
                    push_left(current->right.get());
                }
            }
        }
        
        reference operator*() const { 
            return current->data; 
        }
        
        pointer operator->() const { 
            return &current->data; 
        }
        
        // Prefix increment
        iterator& operator++() {
            advance();
            return *this;
        }
        
        // Postfix increment
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        friend bool operator==(const iterator& a, const iterator& b) { 
            return a.current == b.current; 
        }
        
        friend bool operator!=(const iterator& a, const iterator& b) { 
            return a.current != b.current; 
        }
        
    private:
        void push_left(Node* node) {
            while (node) {
                node_stack.push(node);
                node = node->left.get();
            }
        }
        
        void advance() {
            if (node_stack.empty()) {
                current = nullptr;
                return;
            }
            current = node_stack.top();
            node_stack.pop();
            push_left(current->right.get());
        }
        
        Node* current;
        std::stack<Node*> node_stack;
    };
    
    iterator begin() const {
        return iterator(root.get());
    }
    
    iterator end() const {
        return iterator();
    }
    
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    // Helper function to deep copy a node and its subtrees
    std::unique_ptr<Node> copy_node(const std::unique_ptr<Node>& source) const {
        if (!source) { 
            return nullptr;
        }
        auto new_node = std::make_unique<Node>(source->data);
        new_node->left = copy_node(source->left);
        new_node->right = copy_node(source->right);
        return new_node;
    }
    
    std::unique_ptr<Node> root;
    
    void insert_impl(std::unique_ptr<Node>& node, T value) {
        if (!node) { 
            node = std::make_unique<Node>(value);
            return;
        }
        if (value <= node->data) { 
            insert_impl(node->left, value);
        } else { 
            insert_impl(node->right, value);
        }
    }
    
    bool find_impl(const std::unique_ptr<Node>& node, T value) const {
        if (!node) { 
            return false;
        }
        if (value == node->data) { 
            return true;
        } else if (value < node->data) { 
            return find_impl(node->left, value);
        } else { 
            return find_impl(node->right, value);
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
