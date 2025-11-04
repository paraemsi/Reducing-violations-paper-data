#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insertNode(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return containsNode(root_, value);
}

void BinarySearchTree::insertNode(std::unique_ptr<Node>& current, std::int32_t value)
{
    if(current == nullptr) {
        current = std::make_unique<Node>(value);
    } else {
        if(value <= current->value) {
            insertNode(current->left, value);
        } else {
            insertNode(current->right, value);
        }
    }
}

bool BinarySearchTree::containsNode(const std::unique_ptr<Node>& current, std::int32_t value)
{
    if(current == nullptr) {
        return false;
    }

    if(value == current->value) {
        return true;
    }

    if(value < current->value) {
        return containsNode(current->left, value);
    }

    /* value is greater than current->value */
    return containsNode(current->right, value);
}

}  // namespace binary_search_tree
