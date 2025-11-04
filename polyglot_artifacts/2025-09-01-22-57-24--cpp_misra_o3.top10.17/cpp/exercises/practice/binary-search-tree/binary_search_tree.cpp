#include "binary_search_tree.h"

namespace binary_search_tree {

BinarySearchTree::BinarySearchTree(std::int32_t value)
{
    insert(value);
}

void BinarySearchTree::insert(std::int32_t value)
{
    insert_impl(root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains_impl(root, value);
}

void BinarySearchTree::insert_impl(std::unique_ptr<Node>& node, std::int32_t value)
{
    if (!node)
    {
        node = std::make_unique<Node>(value);
    }
    else
    {
        if ((value <= node->value))
        {
            insert_impl(node->left, value);
        }
        else
        {
            insert_impl(node->right, value);
        }
    }
}

bool BinarySearchTree::contains_impl(const std::unique_ptr<Node>& node, std::int32_t value)
{
    if (!node)
    {
        return false;
    }

    if ((value == node->value))
    {
        return true;
    }

    if ((value < node->value))
    {
        return contains_impl(node->left, value);
    }

    return contains_impl(node->right, value);
}

}  // namespace binary_search_tree
