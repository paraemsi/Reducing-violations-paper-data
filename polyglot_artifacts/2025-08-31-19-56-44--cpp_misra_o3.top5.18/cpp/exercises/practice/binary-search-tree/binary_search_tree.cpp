#include "binary_search_tree.h"
#include <memory>   // for std::make_unique

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insertNode(root_, value);
}

bool BinarySearchTree::search(std::int32_t value) const
{
    return searchNode(root_, value);
}

void BinarySearchTree::insertNode(std::unique_ptr<Node>& node, std::int32_t value)
{
    if (node == nullptr)
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

bool BinarySearchTree::searchNode(const std::unique_ptr<Node>& node, std::int32_t value)
{
    if (node == nullptr)
    {
        return false;
    }

    if (value == node->data)
    {
        return true;
    }

    if (value < node->data)
    {
        return searchNode(node->left, value);
    }
    else
    {
        return searchNode(node->right, value);
    }
}

}  // namespace binary_search_tree
