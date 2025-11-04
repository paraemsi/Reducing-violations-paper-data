#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert_impl(root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains_impl(root, value);
}

void BinarySearchTree::insert_impl(std::unique_ptr<BinarySearchTree::Node>& subtree, std::int32_t value)
{
    if (subtree == nullptr)
    {
        subtree = std::make_unique<Node>(value);
    }
    else
    {
        if (value <= subtree->data)
        {
            insert_impl(subtree->left, value);
        }
        else
        {
            insert_impl(subtree->right, value);
        }
    }
}

bool BinarySearchTree::contains_impl(const std::unique_ptr<BinarySearchTree::Node>& subtree, std::int32_t value) const
{
    if (subtree == nullptr)
    {
        return false;
    }

    if (value == subtree->data)
    {
        return true;
    }

    if (value < subtree->data)
    {
        return contains_impl(subtree->left, value);
    }

    return contains_impl(subtree->right, value);
}

}  // namespace binary_search_tree
