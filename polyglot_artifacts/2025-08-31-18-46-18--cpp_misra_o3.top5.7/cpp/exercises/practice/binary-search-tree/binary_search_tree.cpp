#include "binary_search_tree.h"

namespace binary_search_tree {

Tree::Tree(value_type data) : m_root{ new Node{ data, nullptr, nullptr } }
{
}

Tree::~Tree()
{
    destroy(m_root);
}

void Tree::insert(value_type data)
{
    insert_node(m_root, data);
}

bool Tree::contains(value_type data) const
{
    return contains_node(m_root, data);
}

void Tree::insert_node(Node*& node, value_type data)
{
    if (node == nullptr)
    {
        node = new Node{ data, nullptr, nullptr };
    }
    else
    {
        if (data <= node->data)
        {
            insert_node(node->left, data);
        }
        else
        {
            insert_node(node->right, data);
        }
    }
}

bool Tree::contains_node(const Node* node, value_type data)
{
    if (node == nullptr)
    {
        return false;
    }

    if (data == node->data)
    {
        return true;
    }

    if (data < node->data)
    {
        return contains_node(node->left, data);
    }

    return contains_node(node->right, data);
}

void Tree::destroy(Node* node)
{
    if (node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

}  // namespace binary_search_tree
