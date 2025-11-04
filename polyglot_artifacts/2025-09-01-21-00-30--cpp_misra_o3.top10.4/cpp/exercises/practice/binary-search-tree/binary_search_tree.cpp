#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert_impl(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const noexcept
{
    return contains_impl(root_, value);
}

void BinarySearchTree::insert_impl(std::unique_ptr<Node>& node, std::int32_t value)
{
    if (!node) {
        node = std::make_unique<Node>(value);
    } else {
        if ((value <= node->value)) {
            insert_impl(node->left, value);
        } else {
            insert_impl(node->right, value);
        }
    }
}

bool BinarySearchTree::contains_impl(const std::unique_ptr<Node>& node, std::int32_t value) noexcept
{
    if (!node) {
        return false;
    } else {
        if ((value == node->value)) {
            return true;
        } else {
            if ((value < node->value)) {
                return contains_impl(node->left, value);
            } else {
                return contains_impl(node->right, value);
            }
        }
    }
}

}  // namespace binary_search_tree
