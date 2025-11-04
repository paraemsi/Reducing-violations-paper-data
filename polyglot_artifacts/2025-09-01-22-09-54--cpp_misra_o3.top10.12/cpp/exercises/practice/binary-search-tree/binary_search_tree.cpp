#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insertNode(root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return containsNode(root, value);
}

void BinarySearchTree::insertNode(std::unique_ptr<Node>& current, std::int32_t value)
{
    if (current == nullptr)
    {
        current = std::make_unique<Node>(value);
    }
    else
    {
        if ((value <= current->data))
        {
            insertNode(current->left, value);
        }
        else
        {
            insertNode(current->right, value);
        }
    }
}

bool BinarySearchTree::containsNode(const std::unique_ptr<Node>& current, std::int32_t value) const
{
    if (current == nullptr)
    {
        return false;
    }

    if ((value == current->data))
    {
        return true;
    }

    if ((value < current->data))
    {
        return containsNode(current->left, value);
    }
    else
    {
        return containsNode(current->right, value);
    }
}

}  // namespace binary_search_tree
