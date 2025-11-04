#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    if ((root_ == nullptr)) {
        root_ = std::make_unique<Node>(value);
    } else {
        insert_node(root_, value);
    }
}

bool BinarySearchTree::contains(std::int32_t value) const noexcept
{
    return (contains_node(root_, value));
}

void BinarySearchTree::insert_node(std::unique_ptr<Node>& node, std::int32_t value)
{
    if ((node == nullptr)) {
        node = std::make_unique<Node>(value);
        return;
    }

    if ((value <= node->value)) {
        if ((node->left == nullptr)) {
            node->left = std::make_unique<Node>(value);
        } else {
            insert_node(node->left, value);
        }
    } else {
        if ((node->right == nullptr)) {
            node->right = std::make_unique<Node>(value);
        } else {
            insert_node(node->right, value);
        }
    }
}

bool BinarySearchTree::contains_node(const std::unique_ptr<Node>& node, std::int32_t value) noexcept
{
    if ((node == nullptr)) {
        return false;
    }

    if ((value == node->value)) {
        return true;
    }

    if ((value < node->value)) {
        return (contains_node(node->left, value));
    }

    return (contains_node(node->right, value));
}

}  // namespace binary_search_tree
