#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    // Iterator class
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(const binary_tree<T>* node) {
            if (node == nullptr || node->empty_) {
                current = nullptr;
                return;
            }
            // Traverse to the leftmost node
            const binary_tree<T>* curr = node;
            while (curr != nullptr && !curr->empty_) {
                node_stack.push(curr);
                curr = (curr->left_ == nullptr) || curr->left_->empty_ ? nullptr : curr->left_.get();
            }
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
            if (current == nullptr) return *this;
            
            // Move to the right subtree's leftmost node
            const binary_tree<T>* curr = current->right_->empty_ ? nullptr : current->right_.get();
            while (curr != nullptr && !curr->empty_) {
                node_stack.push(curr);
                curr = curr->left_->empty_ ? nullptr : curr->left_.get();
            }
            
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
        
        friend bool operator==(const iterator& a, const iterator& b) { return a.current == b.current; }
        friend bool operator!=(const iterator& a, const iterator& b) { return a.current != b.current; }
        
    private:
        const binary_tree<T>* current;
        mutable std::stack<const binary_tree<T>*> node_stack;
    };
    
    binary_tree() : empty_(true), left_(nullptr), right_(nullptr) {}
    
    void insert(T value) {
        if (empty_) {
            data_ = value;
            empty_ = false;
            left_ = std::make_unique<binary_tree<T>>();
            right_ = std::make_unique<binary_tree<T>>();
            return;
        }
        if (value <= data_) {
            left_->insert(value);
        } else {
            right_->insert(value);
        }
    }
    
    bool contains(T value) const {
        if (empty_) {
            return false;
        }
        if (value == data_) {
            return true;
        } else if ((value < data_)) {
            return left_->contains(value);
        } else {
            return right_->contains(value);
        }
    }
    
    const T& data() const {
        return data_;
    }
    
    const binary_tree<T>* left() const {
        // Check if left_ is valid and not empty
        if ((left_ == nullptr) || (left_->empty_)) {
            return nullptr;
        }
        return left_.get();
    }
    
    const binary_tree<T>* right() const {
        // Check if right_ is valid and not empty
        if ((right_ == nullptr) || (right_->empty_)) {
            return nullptr;
        }
        return right_.get();
    }

    // Iterator functions
    iterator begin() const {
        if (empty_) {
            return iterator();
        }
        return iterator(this);
    }
    
    iterator end() const {
        return iterator();
    }

private:
    T data_{};
    bool empty_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
