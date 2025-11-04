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

void BinarySearchTree::insertNode(std::unique_ptr<Node>& node, std::int32_t value)
{
    if (!node)
    {
        node = std::make_unique<Node>(value);
    }
    else
    {
        if (value <= node->data)
        {
            insertNode(node->left, value);
        }
        else
        {
            insertNode(node->right, value);
        }
    }
}

bool BinarySearchTree::containsNode(const std::unique_ptr<Node>& node, std::int32_t value) const
{
    if (!node)
    {
        return false;
    }
    if (value == node->data)
    {
        return true;
    }
    if (value < node->data)
    {
        return containsNode(node->left, value);
    }
    else
    {
        return containsNode(node->right, value);
    }
}

}  // namespace binary_search_tree
