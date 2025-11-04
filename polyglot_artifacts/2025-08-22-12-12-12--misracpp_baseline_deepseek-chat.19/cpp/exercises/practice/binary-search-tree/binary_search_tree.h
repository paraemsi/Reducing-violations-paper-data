#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <stack>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree(T data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    T data() const {
        return data_;
    }
    
    const binary_tree<T>* left() const {
        return left_.get();
    }
    
    const binary_tree<T>* right() const {
        return right_.get();
    }
    
    void insert(T value) {
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
    
    // Iterator class
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(const binary_tree<T>* root) {
            // Push all left nodes to the stack
            const binary_tree<T>* node = root;
            while (node != nullptr) {
                node_stack.push(node);
                node = node->left();
            }
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            } else {
                current = nullptr;
            }
        }
        
        reference operator*() const {
            if (current == nullptr) {
                // This is not ideal, but we need to return something
                // In a real implementation, we'd throw an exception
                static T dummy;
                return dummy;
            }
            return const_cast<T&>(current->data_);
        }
        
        pointer operator->() const {
            if (current == nullptr) {
                // This is not ideal, but we need to return something
                static T dummy;
                return &dummy;
            }
            return &(const_cast<T&>(current->data_));
        }
        
        iterator& operator++() {
            // Move to the next node in in-order traversal
            if (current == nullptr) {
                return *this;
            }
            
            // Process right subtree
            const binary_tree<T>* node = current->right();
            while (node != nullptr) {
                node_stack.push(node);
                node = node->left();
            }
            
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
        const binary_tree<T>* current;
        mutable std::stack<const binary_tree<T>*> node_stack;
    };
    
    iterator begin() const {
        return iterator(this);
    }
    
    iterator end() const {
        return iterator();
    }
    
private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
    
    // Make iterator a friend to access private members
    friend class iterator;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
