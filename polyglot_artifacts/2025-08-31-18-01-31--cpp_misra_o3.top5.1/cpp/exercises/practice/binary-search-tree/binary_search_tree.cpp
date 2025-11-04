#include "binary_search_tree.h"

namespace binary_search_tree {

Node::Node(std::int32_t val) noexcept
    : data(val),
      left(nullptr),
      right(nullptr)
{
    /* empty */
}

void BinarySearchTree::insert(std::int32_t value)
{
    insertHelper(m_root, value);
}

void BinarySearchTree::insertHelper(Node*& current, std::int32_t value)
{
    if (current == nullptr)
    {
        current = new Node(value);
        return;
    }

    /* value less than or equal goes to the left subtree */
    if ((value <= current->data))
    {
        insertHelper(current->left, value);
    }
    else
    {
        insertHelper(current->right, value);
    }
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return containsHelper(m_root, value);
}

bool BinarySearchTree::containsHelper(const Node* current, std::int32_t value) const
{
    if (current == nullptr)
    {
        return false;
    }

    if ((value == current->data))
    {
        return true;
    }

    if ((value < current->data))
    {
        return containsHelper(current->left, value);
    }

    return containsHelper(current->right, value);
}

}  // namespace binary_search_tree
binary_search_tree::BinarySearchTree::~BinarySearchTree() noexcept
{
    destroy(m_root);
}

void binary_search_tree::BinarySearchTree::destroy(Node* node) noexcept
{
    if (node == nullptr)
    {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}
