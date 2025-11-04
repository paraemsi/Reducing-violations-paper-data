#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(ValueType value)
{
    insert(root, value);
}

void BinarySearchTree::insert(std::unique_ptr<Node>& subtree, ValueType value)
{
    if((subtree == nullptr))
    {
        subtree = std::make_unique<Node>(value);
    }
    else
    {
        if((value <= subtree->value))
        {
            insert(subtree->left, value);
        }
        else
        {
            insert(subtree->right, value);
        }
    }
}

bool BinarySearchTree::contains(ValueType value) const noexcept
{
    return contains(root, value);
}

bool BinarySearchTree::contains(const std::unique_ptr<Node>& subtree, ValueType value) const noexcept
{
    if((subtree == nullptr))
    {
        return false;
    }

    if((value == subtree->value))
    {
        return true;
    }

    if((value < subtree->value))
    {
        return contains(subtree->left, value);
    }

    return contains(subtree->right, value);
}

}  // namespace binary_search_tree
