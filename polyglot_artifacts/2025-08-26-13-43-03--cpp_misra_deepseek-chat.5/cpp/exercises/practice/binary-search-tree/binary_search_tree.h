#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : is_initialized_(false) {}
    
    void insert(T value) {
        if (!is_initialized_) {
            data_ = value;
            is_initialized_ = true;
            return;
        }
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>();
                left_->insert(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree>();
                right_->insert(value);
            }
        }
    }
    
    bool contains(T value) const {
        if (!is_initialized_) {
            return false;
        }
        if (value == data_) {
            return true;
        } else if (value <= data_) {
            return left_ ? left_->contains(value) : false;
        } else {
            return right_ ? right_->contains(value) : false;
        }
    }
    
    const T& data() const {
        return data_;
    }
    
    const binary_tree& left() const {
        static binary_tree empty_tree;
        if (left_) {
            return *left_;
        }
        return empty_tree;
    }
    
    const binary_tree& right() const {
        static binary_tree empty_tree;
        if (right_) {
            return *right_;
        }
        return empty_tree;
    }

    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        
        explicit iterator(const binary_tree* root) {
            // Push all left nodes to reach the first element
            push_left(root);
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            } else {
                current = nullptr;
            }
        }
        
        reference operator*() const {
            return const_cast<T&>(current->data_);
        }
        
        pointer operator->() const {
            return &(operator*());
        }
        
        iterator& operator++() {
            // Make sure current is valid
            if (current == nullptr) {
                return *this;
            }
            // Push the right child and all its left children
            if (current->right_ && current->right_->is_initialized_) {
                push_left(current->right_.get());
            }
            if (stack.empty()) {
                current = nullptr;
            } else {
                current = stack.top();
                stack.pop();
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
        void push_left(const binary_tree* node) {
            while (node != nullptr && node->is_initialized_) {
                stack.push(node);
                node = node->left_.get();
            }
        }
        
        const binary_tree* current;
        std::stack<const binary_tree*> stack;
    };
    
    iterator begin() const {
        if (!is_initialized_) {
            return end();
        }
        return iterator(this);
    }
    
    iterator end() const {
        return iterator(nullptr);
    }

private:
    T data_{};
    bool is_initialized_{false};
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
