#include "binary_search_tree.h"

#include <memory>

namespace binary_search_tree {

void BinarySearchTree::insert(int_type value)
{
    insertRecursive(root, value);
}

void BinarySearchTree::insertRecursive(std::unique_ptr<Node>& node, int_type value)
{
    if (node == nullptr)
    {
        node = std::make_unique<Node>(value);
    }
    else
    {
        if ((value <= node->data))
        {
            insertRecursive(node->left, value);
        }
        else
        {
            insertRecursive(node->right, value);
        }
    }
}

bool BinarySearchTree::contains(int_type value) const
{
    return containsRecursive(root, value);
}

bool BinarySearchTree::containsRecursive(const std::unique_ptr<Node>& node, int_type value) const
{
    if (node == nullptr)
    {
        return false;
    }
    else
    {
        if ((value == node->data))
        {
            return true;
        }
        else
        {
            if ((value < node->data))
            {
                return containsRecursive(node->left, value);
            }
            else
            {
                return containsRecursive(node->right, value);
            }
        }
    }
}

}  // namespace binary_search_tree
