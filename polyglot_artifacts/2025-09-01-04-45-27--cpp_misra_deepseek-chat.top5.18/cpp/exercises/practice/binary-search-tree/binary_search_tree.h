#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <iterator>
#include <string>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : is_empty(true), left_(nullptr), right_(nullptr) {}
    
    explicit binary_tree(T value) : is_empty(false), data_(value), left_(nullptr), right_(nullptr) {}
    
    void insert(T value) {
        if (is_empty) {
            data_ = value;
            is_empty = false;
            return;
        }
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
    
    bool find(T value) const {
        if (is_empty) {
            return false;
        }
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return left_ ? left_->find(value) : false;
        } else {
            return right_ ? right_->find(value) : false;
        }
    }
    
    const T& data() const {
        // It's important that data() is never called on an empty tree
        // According to the tests, this should always be valid
        return data_;
    }
    
    const binary_tree* left() const {
        if (left_ && !left_->is_empty) {
            return left_.get();
        }
        return nullptr;
    }
    
    const binary_tree* right() const {
        if (right_ && !right_->is_empty) {
            return right_.get();
        }
        return nullptr;
    }
    
    // Iterator support using in-order traversal
    std::vector<T> in_order() const {
        std::vector<T> result;
        if (!is_empty) {
            in_order_helper(result);
        }
        return result;
    }
    
    auto begin() const {
        auto elements = in_order();
        return elements.begin();
    }
    
    auto end() const {
        auto elements = in_order();
        return elements.end();
    }
    
private:
    void in_order_helper(std::vector<T>& result) const {
        if (left_) {
            left_->in_order_helper(result);
        }
        result.push_back(data_);
        if (right_) {
            right_->in_order_helper(result);
        }
    }
    
    bool is_empty;
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
