#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert_node(root_, value);
}

bool BinarySearchTree::search(std::int32_t value) const
{
    return search_node(root_, value);
}

void BinarySearchTree::insert_node(std::unique_ptr<Node>& node, std::int32_t value)
{
    if (node == nullptr)
    {
        node = std::make_unique<Node>(value);
    }
    else
    {
        if (value <= node->data)
        {
            insert_node(node->left, value);
        }
        else
        {
            insert_node(node->right, value);
        }
    }
}

bool BinarySearchTree::search_node(const std::unique_ptr<Node>& node,
                                   std::int32_t                value) const
{
    if (node == nullptr)
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
                return search_node(node->left, value);
            }
            else
            {
                return search_node(node->right, value);
            }
        }
    }
}

}  // namespace binary_search_tree
