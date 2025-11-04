#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <functional>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : data_(), is_empty_(true), left_(nullptr), right_(nullptr) {}
    
    binary_tree(T value) 
        : data_(value), is_empty_(false), left_(nullptr), right_(nullptr) {}
    
    // Insert a value into the tree
    void insert(T value) {
        if (is_empty_) {
            data_ = value;
            is_empty_ = false;
            return;
        }
        
        if (value <= data_) {
            if (left_ == nullptr) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (right_ == nullptr) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
        }
    }
    
    // Get the data of the root node
    T data() const {
        return data_;
    }
    
    // Get the left subtree
    const binary_tree* left() const {
        if (left_ == nullptr) {
            return nullptr;
        }
        return left_.get();
    }
    
    // Get the right subtree
    const binary_tree* right() const {
        if (right_ == nullptr) {
            return nullptr;
        }
        return right_.get();
    }
    
private:
    T data_;
    bool is_empty_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
