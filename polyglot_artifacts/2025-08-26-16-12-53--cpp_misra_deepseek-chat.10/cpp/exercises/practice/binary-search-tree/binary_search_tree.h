#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <functional>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data);
    void insert(const T& value);
    T data() const;
    const binary_tree<T>* left() const;
    const binary_tree<T>* right() const;

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

// Template implementation
namespace binary_search_tree {

template<typename T>
binary_tree<T>::binary_tree(const T& data) 
    : data_(data), left_(nullptr), right_(nullptr) {}

template<typename T>
void binary_tree<T>::insert(const T& value) {
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

template<typename T>
T binary_tree<T>::data() const {
    return data_;
}

template<typename T>
const binary_tree<T>* binary_tree<T>::left() const {
    return left_.get();
}

template<typename T>
const binary_tree<T>* binary_tree<T>::right() const {
    return right_.get();
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
