#include "binary_search_tree.h"
#include <cstdint>
#include <cstddef>

#if 0
namespace binary_search_tree {

BinarySearchTree::BinarySearchTree() noexcept : root(nullptr)
{
}

BinarySearchTree::~BinarySearchTree() noexcept
{
    destroyNode(root);
}

void BinarySearchTree::insert(std::int32_t value)
{
    root = insertNode(root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return containsNode(root, value);
}

/* static */ BinarySearchTree::Node* BinarySearchTree::insertNode(Node* node, std::int32_t value)
{
    if(node == nullptr)
    {
        node = new Node(value);
    }
    else
    {
        if(value <= node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else
        {
            node->right = insertNode(node->right, value);
        }
    }
    return node;
}

/* static */ bool BinarySearchTree::containsNode(const Node* node, std::int32_t value) noexcept
{
    if(node == nullptr)
    {
        return false;
    }

    if(value == node->data)
    {
        return true;
    }

    if(value < node->data)
    {
        return containsNode(node->left, value);
    }

    return containsNode(node->right, value);
}

/* static */ void BinarySearchTree::destroyNode(Node* node) noexcept
{
    if(node != nullptr)
    {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}

}  // namespace binary_search_tree
#endif
