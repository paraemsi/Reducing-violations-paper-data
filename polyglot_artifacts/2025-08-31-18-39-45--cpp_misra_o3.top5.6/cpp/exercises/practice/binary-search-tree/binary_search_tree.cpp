#include "binary_search_tree.h"

#include <memory>

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insertNode(m_root, value);
}

void BinarySearchTree::insertNode(std::unique_ptr<Node>& root, std::int32_t value)
{
    if (root == nullptr) {
        root = std::make_unique<Node>(value);
    } else {
        if (value <= root->value) {
            insertNode(root->left, value);
        } else {
            insertNode(root->right, value);
        }
    }
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return containsNode(m_root, value);
}

bool BinarySearchTree::containsNode(const std::unique_ptr<Node>& root, std::int32_t value) const
{
    if (root == nullptr) {
        return false;
    }

    if (value == root->value) {
        return true;
    }

    if (value < root->value) {
        return containsNode(root->left, value);
    } else {
        return containsNode(root->right, value);
    }
}

}  // namespace binary_search_tree
