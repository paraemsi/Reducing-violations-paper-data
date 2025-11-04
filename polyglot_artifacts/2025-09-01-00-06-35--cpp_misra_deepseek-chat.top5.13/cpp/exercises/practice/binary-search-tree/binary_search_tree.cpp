#include "binary_search_tree.h"
#include <memory>

namespace binary_search_tree {

template<typename T>
void binary_tree<T>::insert(T value) {
    // If this is an empty node, set its data
    if (left_ == nullptr) {
        data_ = value;
        left_ = std::make_unique<binary_tree>();
        right_ = std::make_unique<binary_tree>();
    } else {
        insert_impl(value);
    }
}

template<typename T>
void binary_tree<T>::insert_impl(T value) {
    if (value <= data_) {
        left_->insert(value);
    } else {
        right_->insert(value);
    }
}

template<typename T>
bool binary_tree<T>::contains(T value) const {
    // Check if this node is empty
    if (left_ == nullptr) {
        return false;
    }
    if (value == data_) {
        return true;
    } else if (value < data_) {
        return left_->contains(value);
    } else {
        return right_->contains(value);
    }
}

template<typename T>
const T* binary_tree<T>::data() const {
    // Return nullptr if the node is empty
    if (left_ == nullptr) {
        return nullptr;
    }
    return &data_;
}

template<typename T>
const binary_tree<T>* binary_tree<T>::left() const {
    // Always return the left child, even if it's empty
    return left_.get();
}

template<typename T>
const binary_tree<T>* binary_tree<T>::right() const {
    // Always return the right child, even if it's empty
    return right_.get();
}

// Explicit template instantiation for int
template class binary_tree<int>;

}  // namespace binary_search_tree
