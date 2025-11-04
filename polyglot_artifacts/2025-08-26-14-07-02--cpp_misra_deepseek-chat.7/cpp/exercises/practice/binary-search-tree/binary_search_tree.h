#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <functional>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }
    
    const T& data() const {
        return data_;
    }
    
    const binary_tree* left() const {
        return left_.get();
    }
    
    const binary_tree* right() const {
        return right_.get();
    }
    
    // Iterator class for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(const binary_tree* root) {
            // Push all left nodes to reach the first element
            push_left(root);
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            } else {
                current = nullptr;
            }
        }
        
        reference operator*() const { return current->data_; }
        pointer operator->() const { return &current->data_; }
        
        // Prefix increment
        iterator& operator++() {
            // If there's a right child, push its left subtree
            if (current->right_) {
                push_left(current->right_.get());
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
        
        // Postfix increment
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
        
    private:
        void push_left(const binary_tree* node) {
            while (node) {
                node_stack.push(node);
                node = node->left_.get();
            }
        }
        
        const binary_tree* current;
        mutable std::stack<const binary_tree*> node_stack;
    };
    
    iterator begin() const {
        return iterator(this);
    }
    
    iterator end() const {
        return iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

// Helper function to create a tree from a list of values
template<typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) return nullptr;
    
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
