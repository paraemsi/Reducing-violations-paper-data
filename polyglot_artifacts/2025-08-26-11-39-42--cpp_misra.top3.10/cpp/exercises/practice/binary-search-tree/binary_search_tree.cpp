#include "binary_search_tree.h"

namespace binary_search_tree {

Node::Node(value_type val)
    : data(val), left(nullptr), right(nullptr)
{
}

Node::~Node()
{
    // No dynamic memory in Node itself
}

BinarySearchTree::BinarySearchTree()
    : root(nullptr)
{
}

BinarySearchTree::~BinarySearchTree()
{
    destroy(root);
}

void BinarySearchTree::insert(value_type value)
{
    insert(root, value);
}

void BinarySearchTree::insert(Node*& node, value_type value)
{
    if (node == nullptr)
    {
        node = new Node(value);
    }
    else if (value <= node->data)
    {
        insert(node->left, value);
    }
    else
    {
        insert(node->right, value);
    }
}

bool BinarySearchTree::search(value_type value) const
{
    return search(root, value);
}

bool BinarySearchTree::search(const Node* node, value_type value) const
{
    if (node == nullptr)
    {
        return false;
    }
    if (value == node->data)
    {
        return true;
    }
    else if (value < node->data)
    {
        return search(node->left, value);
    }
    else
    {
        return search(node->right, value);
    }
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

}  // namespace binary_search_tree
