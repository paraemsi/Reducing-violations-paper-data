#include "binary_search_tree.h"
#include <utility>

#if 0
namespace binary_search_tree {

tree::tree(int data) : data_{data} {}

tree::tree(const tree& other) : data_{other.data_} {
    if (other.left_) {
        left_ = new tree(*other.left_);
    }
    if (other.right_) {
        right_ = new tree(*other.right_);
    }
}

tree::tree(tree&& other) noexcept
    : data_{other.data_}, left_{other.left_}, right_{other.right_} {
    other.left_  = nullptr;
    other.right_ = nullptr;
}

tree& tree::operator=(const tree& other) {
    if (this == &other) {
        return *this;
    }
    delete left_;
    delete right_;
    left_ = right_ = nullptr;

    data_ = other.data_;
    if (other.left_) {
        left_ = new tree(*other.left_);
    }
    if (other.right_) {
        right_ = new tree(*other.right_);
    }
    return *this;
}

tree& tree::operator=(tree&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete left_;
    delete right_;
    data_  = other.data_;
    left_  = other.left_;
    right_ = other.right_;
    other.left_  = nullptr;
    other.right_ = nullptr;
    return *this;
}

int tree::data() const {
    return data_;
}

tree* tree::left() {
    return left_;
}

const tree* tree::left() const {
    return left_;
}

tree* tree::right() {
    return right_;
}

const tree* tree::right() const {
    return right_;
}

void tree::insert(int value) {
    if (value <= data_) {
        if (left_) {
            left_->insert(value);
        } else {
            left_ = new tree(value);
        }
    } else {
        if (right_) {
            right_->insert(value);
        } else {
            right_ = new tree(value);
        }
    }
}

bool tree::contains(int value) const {
    if (value == data_) {
        return true;
    }
    if (value < data_) {
        return left_ ? left_->contains(value) : false;
    }
    return right_ ? right_->contains(value) : false;
}

tree::~tree() {
    delete left_;
    delete right_;
}

}  // namespace binary_search_tree
#endif
