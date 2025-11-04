#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert_impl(root_, value);
}

void BinarySearchTree::insert_impl(std::unique_ptr<Node>& current, std::int32_t value)
{
    if (current == nullptr) {
        current = std::make_unique<Node>(value);
    } else {
        if (value <= current->value) {
            insert_impl(current->left, value);
        } else {
            insert_impl(current->right, value);
        }
    }
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains_impl(root_, value);
}

bool BinarySearchTree::contains_impl(const std::unique_ptr<Node>& current, std::int32_t value) const
{
    if (current == nullptr) {
        return false;
    }
    if (value == current->value) {
        return true;
    }
    if (value < current->value) {
        return contains_impl(current->left, value);
    }
    return contains_impl(current->right, value);
}

}  // namespace binary_search_tree
