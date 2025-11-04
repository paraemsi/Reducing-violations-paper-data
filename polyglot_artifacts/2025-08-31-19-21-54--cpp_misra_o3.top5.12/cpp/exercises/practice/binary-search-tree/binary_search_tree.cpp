#include "binary_search_tree.h"

#include <memory>

namespace binary_search_tree {

void BinarySearchTree::insert(BinarySearchTree::ValueType value) {
    insertNode(root, value);
}

bool BinarySearchTree::contains(BinarySearchTree::ValueType value) const {
    return containsNode(root, value);
}

void BinarySearchTree::insertNode(std::unique_ptr<Node>& current, BinarySearchTree::ValueType value) {
    if (current == nullptr) {
        current = std::make_unique<Node>(value);
    } else {
        if (value <= current->data) {
            insertNode(current->left, value);
        } else {
            insertNode(current->right, value);
        }
    }
}

bool BinarySearchTree::containsNode(const std::unique_ptr<Node>& current, BinarySearchTree::ValueType value) {
    bool result{false};

    if (current == nullptr) {
        result = false;
    } else {
        if (value == current->data) {
            result = true;
        } else if (value < current->data) {
            result = containsNode(current->left, value);
        } else {
            result = containsNode(current->right, value);
        }
    }
    return result;
}

}  // namespace binary_search_tree
