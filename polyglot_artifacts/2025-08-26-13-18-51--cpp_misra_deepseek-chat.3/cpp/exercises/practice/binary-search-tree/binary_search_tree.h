#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <functional>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : data_ptr(nullptr) {}
    
    void insert(T value) {
        if (!data_ptr) {
            data_ptr = std::make_unique<T>(value);
            return;
        }
        
        if (value <= *data_ptr) {
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
        if (!data_ptr) {
            return false;
        }
        if (value == *data_ptr) {
            return true;
        } else if (value < *data_ptr) {
            if (left_) {
                return left_->contains(value);
            } else {
                return false;
            }
        } else {
            if (right_) {
                return right_->contains(value);
            } else {
                return false;
            }
        }
    }
    
    const T& data() const { 
        return *data_ptr;
    }
    
    const binary_tree* left() const { 
        if (left_ && left_->data_ptr) {
            return left_.get();
        }
        return nullptr;
    }
    
    const binary_tree* right() const { 
        if (right_ && right_->data_ptr) {
            return right_.get();
        }
        return nullptr;
    }
    
    // In-order traversal
    std::vector<T> in_order() const {
        std::vector<T> result;
        in_order_helper(result);
        return result;
    }
    
    // Iterator support
    using const_iterator = typename std::vector<T>::const_iterator;
    const_iterator begin() const {
        auto elements = in_order();
        return elements.begin();
    }
    const_iterator end() const {
        auto elements = in_order();
        return elements.end();
    }

private:
    std::unique_ptr<T> data_ptr;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    
    void in_order_helper(std::vector<T>& result) const {
        if (left_) {
            left_->in_order_helper(result);
        }
        if (data_ptr) {
            result.push_back(*data_ptr);
        }
        if (right_) {
            right_->in_order_helper(result);
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
