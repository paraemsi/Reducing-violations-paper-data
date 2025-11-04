#include "binary_search_tree.h"
#include <cstdint>
#include <memory>
#include <string>

namespace binary_search_tree {

template<typename T>
binary_tree<T>::binary_tree(T data) 
    : data_(data), left_(nullptr), right_(nullptr) {
}

template<typename T>
const T& binary_tree<T>::data() const {
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

template<typename T>
void binary_tree<T>::insert(T data) {
    if ((data <= data_)) {
        if (left_) {
            left_->insert(data);
        } else {
            left_ = std::make_unique<binary_tree<T>>(data);
        }
    } else {
        if (right_) {
            right_->insert(data);
        } else {
            right_ = std::make_unique<binary_tree<T>>(data);
        }
    }
}

// Explicit instantiations
template class binary_tree<std::int32_t>;
template class binary_tree<std::uint32_t>;
template class binary_tree<std::string>;

}  // namespace binary_search_tree
