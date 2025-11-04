#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert_impl(root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const noexcept
{
    return contains_impl(root, value);
}

BinarySearchTree::~BinarySearchTree() noexcept
{
    clear(root);
    /* ensure dangling pointer is not left behind */
    root = nullptr;
}

void BinarySearchTree::insert_impl(Node*& node, std::int32_t value)
{
    if (node == nullptr)
    {
        node = new Node(value);
    }
    else
    {
        if (value <= node->data)
        {
            insert_impl(node->left, value);
        }
        else
        {
            insert_impl(node->right, value);
        }
    }
}

bool BinarySearchTree::contains_impl(const Node* node, std::int32_t value) noexcept
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
        return contains_impl(node->left, value);
    }

    return contains_impl(node->right, value);
}

void BinarySearchTree::clear(Node* node) noexcept
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

}  // namespace binary_search_tree
