#include "binary_search_tree.h"

namespace binary_search_tree {

Node::Node(bst_value_t v)
    : value(v), left(nullptr), right(nullptr)
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

void BinarySearchTree::destroy(Node* node)
{
    if(node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void BinarySearchTree::insert(bst_value_t value)
{
    insert(root, value);
}

void BinarySearchTree::insert(Node*& node, bst_value_t value)
{
    if(node == nullptr)
    {
        node = new Node(value);
    }
    else if(value <= node->value)
    {
        insert(node->left, value);
    }
    else
    {
        insert(node->right, value);
    }
}

bool BinarySearchTree::search(bst_value_t value) const
{
    return search(root, value);
}

bool BinarySearchTree::search(const Node* node, bst_value_t value) const
{
    if(node == nullptr)
    {
        return false;
    }
    else if(value == node->value)
    {
        return true;
    }
    else if(value < node->value)
    {
        return search(node->left, value);
    }
    else
    {
        return search(node->right, value);
    }
}

}  // namespace binary_search_tree
