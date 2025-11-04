#include "binary_search_tree.h"

#include <memory>

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insertImpl(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const noexcept
{
    return containsImpl(root_, value);
}

void BinarySearchTree::insertImpl(std::unique_ptr<Node>& node, std::int32_t value)
{
    if ((node == nullptr)) {
        node = std::unique_ptr<Node>(new Node(value));
    } else {
        if ((value <= node->value)) {
            insertImpl(node->left, value);
        } else {
            insertImpl(node->right, value);
        }
    }
}

bool BinarySearchTree::containsImpl(const std::unique_ptr<Node>& node, std::int32_t value) noexcept
{
    if ((node == nullptr)) {
        return false;
    } else {
        if ((value == node->value)) {
            return true;
        } else {
            if ((value < node->value)) {
                return containsImpl(node->left, value);
            } else {
                return containsImpl(node->right, value);
            }
        }
    }
}

}  // namespace binary_search_tree
