#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    const T& data() const { return data_; }
    const binary_tree<T>* left() const { return left_.get(); }
    const binary_tree<T>* right() const { return right_.get(); }
    
    void insert(const T& value) {
        if ((value <= data_)) {
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
    
    bool contains(const T& value) const {
        if ((value == data_)) {
            return true;
        } else {
            if ((value < data_)) {
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
    }
    
private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

template<typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (size_t i = 1; (i < values.size()); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
