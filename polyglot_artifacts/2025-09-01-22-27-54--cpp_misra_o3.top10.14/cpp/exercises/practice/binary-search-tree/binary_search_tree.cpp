#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert(m_root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains(m_root, value);
}

void BinarySearchTree::insert(std::unique_ptr<Node>& root, std::int32_t value)
{
    if (root == nullptr)
    {
        root = std::make_unique<Node>(value);
    }
    else
    {
        if (value <= root->data)
        {
            insert(root->left, value);
        }
        else
        {
            insert(root->right, value);
        }
    }
}

bool BinarySearchTree::contains(const std::unique_ptr<Node>& root, std::int32_t value) const
{
    if (root == nullptr)
    {
        return false;
    }

    if (value == root->data)
    {
        return true;
    }

    if (value < root->data)
    {
        return contains(root->left, value);
    }

    return contains(root->right, value);
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
{
    m_root = clone(other.m_root);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
    if (this != &other)
    {
        m_root = clone(other.m_root);
    }
    return *this;
}

std::unique_ptr<BinarySearchTree::Node> BinarySearchTree::clone(const std::unique_ptr<Node>& node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    auto new_node = std::make_unique<Node>(node->data);
    new_node->left = clone(node->left);
    new_node->right = clone(node->right);
    return new_node;
}

}  // namespace binary_search_tree
