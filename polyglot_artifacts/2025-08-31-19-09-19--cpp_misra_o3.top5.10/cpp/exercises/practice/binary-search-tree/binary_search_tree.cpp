#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert(root_, value);
}

void BinarySearchTree::insert(std::unique_ptr<Node>& current, std::int32_t value)
{
    if (!current) {
        current = std::make_unique<Node>(value);
    } else {
        if (value <= current->data) {
            insert(current->left, value);
        } else {
            insert(current->right, value);
        }
    }
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains(root_, value);
}

bool BinarySearchTree::contains(const std::unique_ptr<Node>& current, std::int32_t value) const
{
    if (!current) {
        return false;
    }

    if (current->data == value) {
        return true;
    }

    if (value < current->data) {
        return contains(current->left, value);
    }

    return contains(current->right, value);
}

}  // namespace binary_search_tree
