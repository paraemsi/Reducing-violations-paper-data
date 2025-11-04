#include "binary_search_tree.h"
#include <memory>
#include <cstdint>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(T value) {
    if (!is_valid_) {
        data_ = value;
        is_valid_ = true;
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

template <typename T>
bool binary_tree<T>::contains(T value) const {
    if (!is_valid_) {
        return false;
    }
    if (value == data_) {
        return true;
    } else if (value < data_) {
        return (left_ != nullptr) && (left_->contains(value));
    } else {
        return (right_ != nullptr) && (right_->contains(value));
    }
}

template <typename T>
T binary_tree<T>::data() const {
    return data_;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::left() const {
    if (left_ && left_->is_valid_) {
        return std::make_unique<binary_tree<T>>(*left_);
    }
    return nullptr;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::right() const {
    if (right_ && right_->is_valid_) {
        return std::make_unique<binary_tree<T>>(*right_);
    }
    return nullptr;
}

// Explicit instantiations
template class binary_tree<std::int32_t>;

}  // namespace binary_search_tree
