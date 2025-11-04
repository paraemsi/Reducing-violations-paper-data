#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::destroy(Node* const node)
{
    if(node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    } else {
        /* No action required */
    }
}

BinarySearchTree::~BinarySearchTree()
{
    destroy(root);
}

BinarySearchTree::Node* BinarySearchTree::insertNode(Node* const node, const std::int32_t value)
{
    if(node == nullptr) {
        return new Node(value);
    }

    if((value <= node->data)) {
        node->left = insertNode(node->left, value);
    } else {
        node->right = insertNode(node->right, value);
    }
    return node;
}

void BinarySearchTree::insert(const std::int32_t value)
{
    root = insertNode(root, value);
}

bool BinarySearchTree::containsNode(const Node* const node, const std::int32_t value)
{
    if(node == nullptr) {
        return false;
    }

    if((value == node->data)) {
        return true;
    }

    if((value < node->data)) {
        return containsNode(node->left, value);
    } else {
        return containsNode(node->right, value);
    }
}

bool BinarySearchTree::contains(const std::int32_t value) const
{
    return containsNode(root, value);
}

}  // namespace binary_search_tree
