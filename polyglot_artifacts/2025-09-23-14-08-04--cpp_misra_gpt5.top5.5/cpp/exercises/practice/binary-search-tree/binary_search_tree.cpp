#include "binary_search_tree.h"

namespace binary_search_tree {

// ===== Node =====

Node::Node(Node::value_type value) noexcept : data_{value}, left_{}, right_{} {}

void Node::insert(Node::value_type value) {
    if ((value <= data_)) {
        if ((left_ == nullptr)) {
            left_ = std::unique_ptr<Node>(new Node(value));
        } else {
            left_->insert(value);
        }
    } else {
        if ((right_ == nullptr)) {
            right_ = std::unique_ptr<Node>(new Node(value));
        } else {
            right_->insert(value);
        }
    }
}

bool Node::contains(Node::value_type value) const noexcept {
    if ((value == data_)) {
        return true;
    }

    if ((value < data_)) {
        if ((left_ != nullptr)) {
            return left_->contains(value);
        } else {
            return false;
        }
    } else {
        if ((right_ != nullptr)) {
            return right_->contains(value);
        } else {
            return false;
        }
    }
}

Node::value_type Node::data() const noexcept {
    return data_;
}

const Node* Node::left() const noexcept {
    return left_.get();
}

const Node* Node::right() const noexcept {
    return right_.get();
}

// ===== BinarySearchTree =====

void BinarySearchTree::insert(BinarySearchTree::value_type value) {
    if ((root_ == nullptr)) {
        root_ = std::unique_ptr<Node>(new Node(value));
    } else {
        root_->insert(value);
    }
}

bool BinarySearchTree::contains(BinarySearchTree::value_type value) const noexcept {
    if ((root_ == nullptr)) {
        return false;
    } else {
        return root_->contains(value);
    }
}

const Node* BinarySearchTree::root() const noexcept {
    return root_.get();
}

}  // namespace binary_search_tree
