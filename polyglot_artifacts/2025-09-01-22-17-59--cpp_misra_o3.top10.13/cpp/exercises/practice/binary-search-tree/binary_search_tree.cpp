#include "binary_search_tree.h"
#include <memory>  // for std::make_unique

namespace binary_search_tree {

BinarySearchTree::Node::Node(value_type v) noexcept
    : value(v), left(nullptr), right(nullptr)
{
}

void BinarySearchTree::Node::insert(value_type v)
{
    if (v <= value)
    {
        if (left == nullptr)
        {
            left = std::make_unique<Node>(v);
        }
        else
        {
            left->insert(v);
        }
    }
    else
    {
        if (right == nullptr)
        {
            right = std::make_unique<Node>(v);
        }
        else
        {
            right->insert(v);
        }
    }
}

bool BinarySearchTree::Node::contains(value_type v) const noexcept
{
    if (v == value)
    {
        return true;
    }
    if (v < value)
    {
        return (left == nullptr) ? false : left->contains(v);
    }
    /* v > value */
    return (right == nullptr) ? false : right->contains(v);
}

void BinarySearchTree::insert(value_type v)
{
    if (root == nullptr)
    {
        root = std::make_unique<Node>(v);
    }
    else
    {
        root->insert(v);
    }
}

bool BinarySearchTree::contains(value_type v) const noexcept
{
    return (root == nullptr) ? false : root->contains(v);
}

}  // namespace binary_search_tree
