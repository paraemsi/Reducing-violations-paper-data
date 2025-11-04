#include "binary_search_tree.h"

#include <memory>

#if 0   // Legacy non-template implementation moved to header
namespace binary_search_tree {

binary_tree::binary_tree(int value)
    : value_(value), left_(nullptr), right_(nullptr) {}

void binary_tree::insert(int value) {
    if (value <= value_) {
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

bool binary_tree::contains(int value) const noexcept {
    if (value == value_) {
        return true;
    }
    if (value < value_) {
        return left_ ? left_->contains(value) : false;
    }
    return right_ ? right_->contains(value) : false;
}

int binary_tree::data() const noexcept {
    return value_;
}

const binary_tree* binary_tree::left() const noexcept {
    return left_.get();
}

const binary_tree* binary_tree::right() const noexcept {
    return right_.get();
}

}  // namespace binary_search_tree
#endif  // Legacy implementation
