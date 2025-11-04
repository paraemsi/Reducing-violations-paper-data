#include "binary_search_tree.h"

#include <cstddef>   // for nullptr_t

namespace binary_search_tree {

BinarySearchTree::~BinarySearchTree() noexcept
{
    destroy(root_);
}

void BinarySearchTree::insert(std::int32_t value)
{
    root_ = insert(root_, value);
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains(root_, value);
}

/* static */ BinarySearchTree::Node* BinarySearchTree::insert(Node* node, std::int32_t value)
{
    if (node == nullptr) {
        return new Node(value);
    } else {
        if (value <= node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }
}

/* static */ bool BinarySearchTree::contains(const Node* node, std::int32_t value)
{
    if (node == nullptr) {
        return false;
    }

    if (value == node->data) {
        return true;
    }

    if (value < node->data) {
        return contains(node->left, value);
    }

    return contains(node->right, value);
}

/* static */ void BinarySearchTree::destroy(Node* node)
{
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

}  // namespace binary_search_tree
