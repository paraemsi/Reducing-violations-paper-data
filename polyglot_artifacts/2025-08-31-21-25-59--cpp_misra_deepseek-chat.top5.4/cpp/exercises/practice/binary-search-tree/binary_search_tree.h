#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <stdexcept>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Remove default constructor, always initialize with data
    explicit binary_tree(T data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    const T& data() const {
        return data_;
    }
    
    const binary_tree* left() const {
        return left_.get();
    }
    
    const binary_tree* right() const {
        return right_.get();
    }
    
    void insert(T value) {
        if ((value <= data_)) {
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
    
private:
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
