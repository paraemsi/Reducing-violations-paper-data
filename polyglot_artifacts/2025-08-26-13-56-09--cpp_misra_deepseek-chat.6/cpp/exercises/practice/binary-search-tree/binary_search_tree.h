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
    binary_tree() = default;

    void insert(T value) {
        if (!initialized_) {
            data_ = value;
            initialized_ = true;
            return;
        }
        
        if (value <= data_) {
            if (left_ == nullptr) {
                left_ = std::make_unique<binary_tree<T>>();
                left_->insert(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (right_ == nullptr) {
                right_ = std::make_unique<binary_tree<T>>();
                right_->insert(value);
            } else {
                right_->insert(value);
            }
        }
    }

    bool contains(T value) const {
        if (!initialized_) {
            return false;
        }
        if (value == data_) {
            return true;
        } else if (value <= data_) {
            if (left_ != nullptr) {
                return left_->contains(value);
            } else {
                return false;
            }
        } else {
            if (right_ != nullptr) {
                return right_->contains(value);
            } else {
                return false;
            }
        }
    }

    T data() const {
        return data_;
    }

    const binary_tree* left() const {
        return left_.get();
    }

    const binary_tree* right() const {
        return right_.get();
    }

    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) {
            // Push all left nodes to the stack
            const binary_tree<T>* current = root;
            while (current != nullptr && current->initialized_) {
                node_stack.push(current);
                current = current->left_.get();
            }
        }

        reference operator*() {
            // Ensure we're not dereferencing an end iterator
            // In a valid use case, this should never be called on an empty stack
            return const_cast<T&>(node_stack.top()->data_);
        }

        pointer operator->() {
            // Ensure we're not dereferencing an end iterator
            // In a valid use case, this should never be called on an empty stack
            return &const_cast<T&>(node_stack.top()->data_);
        }

        iterator& operator++() {
            // Make sure we're not at the end
            if (node_stack.empty()) {
                return *this;
            }
            
            const binary_tree<T>* current = node_stack.top();
            node_stack.pop();
            
            // Move to the right child and push all left children
            current = current->right_.get();
            while (current != nullptr && current->initialized_) {
                node_stack.push(current);
                current = current->left_.get();
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            // Handle cases where one or both are at the end
            if (node_stack.empty() || other.node_stack.empty()) {
                return node_stack.empty() && other.node_stack.empty();
            }
            // Compare the top of the stacks
            return node_stack.top() == other.node_stack.top();
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const binary_tree<T>*> node_stack;
    };

    iterator begin() const {
        if (!initialized_) {
            return iterator();
        }
        return iterator(this);
    }

    iterator end() const {
        return iterator();
    }
    
private:
    T data_{};
    bool initialized_{false};
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
