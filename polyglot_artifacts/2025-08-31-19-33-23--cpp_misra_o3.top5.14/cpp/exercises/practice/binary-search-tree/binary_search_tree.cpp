#include "binary_search_tree.h"

namespace binary_search_tree {

BinarySearchTree::Node::Node(BinarySearchTree::value_type v) :
    data(v),
    left(nullptr),
    right(nullptr)
{
}

void BinarySearchTree::insert(value_type value)
{
    insertRec(root_, value);
}

void BinarySearchTree::insertRec(std::unique_ptr<Node>& current, value_type value)
{
    if((current == nullptr))
    {
        current = std::make_unique<Node>(value);
    }
    else
    {
        if((value <= current->data))
        {
            insertRec(current->left, value);
        }
        else
        {
            insertRec(current->right, value);
        }
    }
}

bool BinarySearchTree::contains(value_type value) const
{
    return containsRec(root_, value);
}

bool BinarySearchTree::containsRec(const std::unique_ptr<Node>& current, value_type value) const
{
    if((current == nullptr))
    {
        return false;
    }
    if((value == current->data))
    {
        return true;
    }
    if((value < current->data))
    {
        return containsRec(current->left, value);
    }
    else
    {
        return containsRec(current->right, value);
    }
}

}  // namespace binary_search_tree
