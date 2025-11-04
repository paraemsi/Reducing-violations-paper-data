#include "binary_search_tree.h"
#include <memory>

namespace binary_search_tree {

void binary_tree::insert(std::int32_t value) {
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

bool binary_tree::contains(std::int32_t value) const {
    if (value == data_) {
        return true;
    } else if (value < data_) {
        return left_ ? left_->contains(value) : false;
    } else {
        return right_ ? right_->contains(value) : false;
    }
}

}  // namespace binary_search_tree
