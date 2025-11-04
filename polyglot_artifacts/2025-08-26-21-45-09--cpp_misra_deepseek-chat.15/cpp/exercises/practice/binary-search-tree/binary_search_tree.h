#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    // Default constructor creates an empty tree
    binary_tree() : is_empty_(true) {}
    explicit binary_tree(const T& value) : data_(value), is_empty_(false) {}
    
    void insert(const T& value) {
        if (is_empty_) {
            data_ = value;
            is_empty_ = false;
            return;
        }
        
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
    
    bool find(const T& value) const {
        if (is_empty_) {
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
        // Assume this is never called on an empty tree, as per tests
        return data_;
    }
    
    const binary_tree<T>* left() const {
        return (left_ && !left_->is_empty_) ? left_.get() : nullptr;
    }
    
    const binary_tree<T>* right() const {
        return (right_ && !right_->is_empty_) ? right_.get() : nullptr;
    }
    
private:
    T data_{};
    bool is_empty_{true};
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
