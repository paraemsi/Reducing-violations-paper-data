#include "binary_search_tree.h"
#include <cstdint>
#include <string>

namespace binary_search_tree {

template<typename T>
binary_tree<T>::binary_tree(T data) : data_(data) {
}

template<typename T>
void binary_tree<T>::insert(T value) {
    if ((value <= data_)) {
        if (left_ == nullptr) {
            left_ = std::make_unique<binary_tree<T>>(value);
        } else {
            left_->insert(value);
        }
    } else {
        if (right_ == nullptr) {
            right_ = std::make_unique<binary_tree<T>>(value);
        } else {
            right_->insert(value);
        }
    }
}

template<typename T>
bool binary_tree<T>::contains(T value) const {
    if ((value == data_)) {
        return true;
    } else if ((value < data_)) {
        if (left_ != nullptr) {
            return left_->contains(value);
        } else {
            return false;
        }
    } else {
        if (right_ != nullptr) {
            return right_->contains(value);
        } else {
            return false;
        }
    }
}

template<typename T>
T binary_tree<T>::data() const {
    return data_;
}

template<typename T>
binary_tree<T>* binary_tree<T>::left() const {
    return left_.get();
}

template<typename T>
binary_tree<T>* binary_tree<T>::right() const {
    return right_.get();
}

// Explicit instantiation for uint32_t
template class binary_tree<std::uint32_t>;
// Also instantiate for std::string to support string tests
template class binary_tree<std::string>;

}  // namespace binary_search_tree
