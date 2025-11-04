#include "binary_search_tree.h"
#include <cstdint>
#include <memory>
#include <string>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(T value) {
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

template <typename T>
bool binary_tree<T>::find(T value) const {
    if (value == data_) {
        return true;
    } else if (value < data_) {
        if (left_) {
            return left_->find(value);
        } else {
            return false;
        }
    } else {
        if (right_) {
            return right_->find(value);
        } else {
            return false;
        }
    }
}

// Explicit instantiation for std::int32_t and std::string
template class binary_tree<std::int32_t>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
