#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : data_{}, left_(nullptr), right_(nullptr) {}
    
    void insert(T value) {
        if (left_ == nullptr && right_ == nullptr && data_ == T{}) {
            // Treat an empty tree as a special case
            data_ = value;
        } else {
            insert_impl(value);
        }
    }
    
    bool contains(T value) const {
        // Handle empty tree
        if (left_ == nullptr && right_ == nullptr && data_ == T{}) {
            return false;
        }
        return contains_impl(value);
    }
    
    const T& data() const {
        // To prevent issues, we need to ensure the tree is not empty
        // Since we can't throw exceptions, we'll need to handle this differently
        // Let's assume the tree is never empty when data() is called, as per the tests
        // But to be safe, we can use a static variable
        static T default_data{};
        if (left_ == nullptr && right_ == nullptr && data_ == T{}) {
            return default_data;
        }
        return data_;
    }
    
    std::unique_ptr<binary_tree> left() const {
        if (left_) {
            // Return a new tree that shares the same structure (not efficient, but maintains const correctness)
            // This is necessary because we can't return a non-const pointer to our internal data from a const method
            auto result = std::make_unique<binary_tree>(left_->data_);
            result->left_ = left_->left_ ? left_->left_->copy() : nullptr;
            result->right_ = left_->right_ ? left_->right_->copy() : nullptr;
            return result;
        }
        return nullptr;
    }
    
    std::unique_ptr<binary_tree> right() const {
        if (right_) {
            auto result = std::make_unique<binary_tree>(right_->data_);
            result->left_ = right_->left_ ? right_->left_->copy() : nullptr;
            result->right_ = right_->right_ ? right_->right_->copy() : nullptr;
            return result;
        }
        return nullptr;
    }
    
    // Helper function to copy the tree
    std::unique_ptr<binary_tree> copy() const {
        auto new_tree = std::make_unique<binary_tree>(data_);
        new_tree->left_ = left_ ? left_->copy() : nullptr;
        new_tree->right_ = right_ ? right_->copy() : nullptr;
        return new_tree;
    }
    
private:
    T data_{};
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    
    // Private constructor for creating nodes with data
    explicit binary_tree(T value) : data_(value), left_(nullptr), right_(nullptr) {}
    
    void insert_impl(T value) {
        if (value <= data_) {
            if (left_) {
                left_->insert_impl(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert_impl(value);
            } else {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }
    
    bool contains_impl(T value) const {
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return left_ ? left_->contains_impl(value) : false;
        } else {
            return right_ ? right_->contains_impl(value) : false;
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
