#include "binary_search_tree.h"

namespace binary_search_tree {

BinarySearchTree::BinarySearchTree() noexcept : root_(nullptr)
{
}

BinarySearchTree::~BinarySearchTree()
{
    destroy(root_);
}

void BinarySearchTree::insert(std::int32_t value)
{
    insert(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains(root_, value);
}

/* static */ void BinarySearchTree::destroy(Node* node) noexcept
{
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

/* static */ void BinarySearchTree::insert(Node*& node, std::int32_t value)
{
    if (node == nullptr) {
        node = new Node(value);
    } else {
        if (value <= node->value) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }
}

/* static */ bool BinarySearchTree::contains(const Node* node, std::int32_t value)
{
    if (node == nullptr) {
        return false;
    }

    if (value == node->value) {
        return true;
    }

    if (value < node->value) {
        return contains(node->left, value);
    }
    return contains(node->right, value);
}

}  // namespace binary_search_tree
