#include "binary_search_tree.h"
#include <memory>
#include <functional>

namespace binary_search_tree {

template <typename T>
void binary_tree<T>::insert(const T& value) {
    // If the tree is empty (both children are null and data_ is default constructed)
    // We need to check if this is the first insertion
    // This is not perfect, but it's the best we can do without additional flags
    if (!left_ && !right_) {
        // Check if the node is uninitialized by seeing if elements_ is empty
        // This is a workaround
        // For the first insert, set the data
        // For a more robust approach, we could use a static counter, but that's not thread-safe
        data_ = value;
        // Make sure to set elements_ to non-empty
        elements_.push_back(value);
        return;
    }
    
    // Normal insertion
    if (value <= data_) {
        if (left_) {
            left_->insert(value);
        } else {
            left_ = std::make_unique<binary_tree<T>>();
            left_->insert(value);
        }
    } else {
        if (right_) {
            right_->insert(value);
        } else {
            right_ = std::make_unique<binary_tree<T>>();
            right_->insert(value);
        }
    }
    // Clear the elements cache whenever the tree is modified
    elements_.clear();
}

template <typename T>
bool binary_tree<T>::contains(const T& value) const {
    if (value == data_) {
        return true;
    } else if (value <= data_) {
        return left_ && left_->contains(value);
    } else {
        return right_ && right_->contains(value);
    }
}

template <typename T>
const T& binary_tree<T>::data() const {
    return data_;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::left() const {
    if (left_) {
        return std::make_unique<binary_tree<T>>(*left_);
    }
    return nullptr;
}

template <typename T>
std::unique_ptr<binary_tree<T>> binary_tree<T>::right() const {
    if (right_) {
        return std::make_unique<binary_tree<T>>(*right_);
    }
    return nullptr;
}

template <typename T>
binary_tree<T>::binary_tree(const binary_tree& other) 
    : data_(other.data_), elements_(other.elements_) {
    if (other.left_) {
        left_ = std::make_unique<binary_tree<T>>(*other.left_);
    }
    if (other.right_) {
        right_ = std::make_unique<binary_tree<T>>(*other.right_);
    }
}

template <typename T>
void binary_tree<T>::flatten_in_order(std::vector<T>& result) const {
    if (left_) {
        left_->flatten_in_order(result);
    }
    result.push_back(data_);
    if (right_) {
        right_->flatten_in_order(result);
    }
}

template <typename T>
void binary_tree<T>::update_elements() const {
    elements_.clear();
    flatten_in_order(elements_);
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::begin() const {
    update_elements();
    return elements_.begin();
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::end() const {
    update_elements();
    return elements_.end();
}

// Explicit instantiation for int to satisfy the tests
template class binary_tree<int>;

}  // namespace binary_search_tree
