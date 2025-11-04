#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains(root_, value);
}

void BinarySearchTree::insert(std::unique_ptr<Node>& node, std::int32_t value)
{
    if (!node)
    {
        node = std::make_unique<Node>(value);
    }
    else
    {
        if (value <= node->data)
        {
            insert(node->left, value);
        }
        else
        {
            insert(node->right, value);
        }
    }
}

bool BinarySearchTree::contains(const std::unique_ptr<Node>& node, std::int32_t value) const
{
    if (!node)
    {
        return false;
    }
    else
    {
        if (value == node->data)
        {
            return true;
        }
        else
        {
            if (value < node->data)
            {
                return contains(node->left, value);
            }
            else
            {
                return contains(node->right, value);
            }
        }
    }
}

}  // namespace binary_search_tree
