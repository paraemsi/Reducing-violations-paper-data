#include "binary_search_tree.h"

namespace binary_search_tree {

BinarySearchTree::~BinarySearchTree()
{
    destroy(root_);
}

void BinarySearchTree::insert(ValueType value)
{
    root_ = insertNode(root_, value);
}

bool BinarySearchTree::search(ValueType value) const
{
    return searchNode(root_, value);
}

BinarySearchTree::Node* BinarySearchTree::insertNode(Node* node, ValueType value)
{
    if (node == nullptr)
    {
        Node* const newNode = new Node{value, nullptr, nullptr};
        return newNode;
    }

    if ((value <= node->data))
    {
        node->left = insertNode(node->left, value);
    }
    else
    {
        node->right = insertNode(node->right, value);
    }

    return node;
}

bool BinarySearchTree::searchNode(const Node* node, ValueType value)
{
    if (node == nullptr)
    {
        return false;
    }

    if (value == node->data)
    {
        return true;
    }

    if ((value < node->data))
    {
        return searchNode(node->left, value);
    }

    return searchNode(node->right, value);
}

void BinarySearchTree::destroy(Node* node)
{
    if (node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

} // namespace binary_search_tree
