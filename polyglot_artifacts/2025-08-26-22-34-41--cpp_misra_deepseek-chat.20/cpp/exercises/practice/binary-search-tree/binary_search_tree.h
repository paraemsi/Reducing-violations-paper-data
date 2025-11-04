#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    // Remove the default constructor, always construct with a value
    explicit binary_tree(T value) : data_(value), left_(nullptr), right_(nullptr) {}
    
    void insert(T value) {
        if (value <= data_) {
            if (left_ == nullptr) {
                left_ = new binary_tree(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (right_ == nullptr) {
                right_ = new binary_tree(value);
            } else {
                right_->insert(value);
            }
        }
    }
    
    bool find(T value) const {
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return (left_ != nullptr) && left_->find(value);
        } else {
            return (right_ != nullptr) && right_->find(value);
        }
    }
    
    const T& data() const { 
        return data_; 
    }
    const binary_tree* left() const { return left_; }
    const binary_tree* right() const { return right_; }
    
private:
    T data_;
    binary_tree* left_;
    binary_tree* right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
