#include "binary_search_tree.h"

namespace binary_search_tree
{

BinarySearchTree::BinarySearchTree() noexcept = default;

BinarySearchTree::~BinarySearchTree() noexcept
{
    destroy_subtree(root_);
}

void BinarySearchTree::destroy_subtree(Node* const node) noexcept
{
    if ((node != nullptr))
    {
        destroy_subtree(node->left);
        destroy_subtree(node->right);
        delete node;
    }
}

BinarySearchTree::Node* BinarySearchTree::insert(Node* const node, const std::int32_t value)
{
    if ((node == nullptr))
    {
        return new Node(value);
    }

    if ((value <= (node->data)))
    {
        node->left = insert(node->left, value);
    }
    else
    {
        node->right = insert(node->right, value);
    }

    return node;
}

void BinarySearchTree::insert(const std::int32_t value)
{
    root_ = insert(root_, value);
}

bool BinarySearchTree::contains(const Node* const node, const std::int32_t value) noexcept
{
    if ((node == nullptr))
    {
        return false;
    }

    if ((value == (node->data)))
    {
        return true;
    }

    if ((value < (node->data)))
    {
        return contains(node->left, value);
    }

    return contains(node->right, value);
}

bool BinarySearchTree::contains(const std::int32_t value) const noexcept
{
    return contains(root_, value);
}

}  // namespace binary_search_tree
