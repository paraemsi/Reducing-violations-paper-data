#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <stdexcept>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
    
    binary_tree(const std::vector<T>& values) {
        if (values.empty()) {
            throw std::invalid_argument("Cannot create tree from empty vector");
        }
        data_ = values[0];
        left_ = nullptr;
        right_ = nullptr;
        
        auto size = static_cast<std::uint64_t>(values.size());
        for (std::uint64_t i = 1; i < size; ++i) {
            insert(values[i]);
        }
    }
    
    ~binary_tree() {
        // unique_ptr will handle cleanup automatically
    }
    
    // Delete copy operations to prevent accidental copying
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }
    
    const T& data() const {
        return data_;
    }
    
    const std::unique_ptr<binary_tree>& left() const {
        return left_;
    }
    
    const std::unique_ptr<binary_tree>& right() const {
        return right_;
    }
    
    // Iterator support for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::int64_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : current_(nullptr) {}
        
        explicit iterator(const binary_tree* root) {
            if (root) {
                push_left(root);
                if (!stack_.empty()) {
                    current_ = stack_.back();
                    stack_.pop_back();
                } else {
                    current_ = nullptr;
                }
            } else {
                current_ = nullptr;
            }
        }
        
        reference operator*() const {
            return current_->data_;
        }
        
        pointer operator->() const {
            return &current_->data_;
        }
        
        iterator& operator++() {
            if (current_->right_) {
                push_left(current_->right_.get());
            }
            
            if (!stack_.empty()) {
                current_ = stack_.back();
                stack_.pop_back();
            } else {
                current_ = nullptr;
            }
            
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const {
            return (current_ == other.current_);
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        
    private:
        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        
        const binary_tree* current_;
        std::vector<const binary_tree*> stack_;
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

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
