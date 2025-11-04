#include "binary_search_tree.h"

#include <cstddef>

namespace binary_search_tree {

BinarySearchTree::BinarySearchTree() noexcept : m_root(nullptr)
{
}

BinarySearchTree::~BinarySearchTree() noexcept
{
    destroy_recursive(m_root);
}

void BinarySearchTree::insert(std::int32_t value) noexcept
{
    m_root = insert_recursive(m_root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const noexcept
{
    return contains_recursive(m_root, value);
}

BinarySearchTree::Node* BinarySearchTree::insert_recursive(Node* node, std::int32_t value) noexcept
{
    if (node == nullptr)
    {
        Node* const new_node = new Node(value);
        return new_node;
    }
    else
    {
        if (value <= node->data)
        {
            node->left = insert_recursive(node->left, value);
        }
        else
        {
            node->right = insert_recursive(node->right, value);
        }
        return node;
    }
}

bool BinarySearchTree::contains_recursive(const Node* node, std::int32_t value) noexcept
{
    if (node == nullptr)
    {
        return false;
    }
    if (value == node->data)
    {
        return true;
    }
    else
    {
        if (value < node->data)
        {
            return contains_recursive(node->left, value);
        }
        else
        {
            return contains_recursive(node->right, value);
        }
    }
}

void BinarySearchTree::destroy_recursive(Node* node) noexcept
{
    if (node != nullptr)
    {
        destroy_recursive(node->left);
        destroy_recursive(node->right);
        delete node;
    }
}

}  // namespace binary_search_tree
