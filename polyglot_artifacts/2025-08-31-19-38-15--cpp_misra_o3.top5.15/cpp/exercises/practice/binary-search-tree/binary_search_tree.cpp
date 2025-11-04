#include "binary_search_tree.h"

#include <cstddef>  // for nullptr

namespace binary_search_tree {

BinarySearchTree::BinarySearchTree() noexcept : root(nullptr)
{
}

BinarySearchTree::BinarySearchTree(std::int32_t rootValue) : root(new Node(rootValue))
{
}

BinarySearchTree::~BinarySearchTree() noexcept
{
    destroySubTree(root);
}

void BinarySearchTree::insert(std::int32_t value)
{
    insertNode(root, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return containsNode(root, value);
}

/* static */ void BinarySearchTree::insertNode(Node*& node, std::int32_t value)
{
    if (node == nullptr)
    {
        node = new Node(value);
    }
    else
    {
        if (value <= node->value)
        {
            insertNode(node->leftChild, value);
        }
        else
        {
            insertNode(node->rightChild, value);
        }
    }
}

/* static */ bool BinarySearchTree::containsNode(const Node* node, std::int32_t value) noexcept
{
    if (node == nullptr)
    {
        return false;
    }

    if (value == node->value)
    {
        return true;
    }

    if (value < node->value)
    {
        return containsNode(node->leftChild, value);
    }
    return containsNode(node->rightChild, value);
}

/* static */ void BinarySearchTree::destroySubTree(Node* node) noexcept
{
    if (node != nullptr)
    {
        destroySubTree(node->leftChild);
        destroySubTree(node->rightChild);
        delete node;
    }
}

}  // namespace binary_search_tree
