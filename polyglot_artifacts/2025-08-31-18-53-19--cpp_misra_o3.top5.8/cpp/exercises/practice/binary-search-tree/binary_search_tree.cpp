#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(std::int32_t value)
{
    insert_node(root_, value);
}

void BinarySearchTree::insert_node(std::unique_ptr<Node>& node, std::int32_t value)
{
    if ((node == nullptr)) {
        node = std::make_unique<Node>(value);
    } else {
        if ((value <= node->data)) {
            insert_node(node->left, value);
        } else {
            insert_node(node->right, value);
        }
    }
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    return contains_node(root_, value);
}

bool BinarySearchTree::contains_node(const std::unique_ptr<Node>& node, std::int32_t value) const
{
    if ((node == nullptr)) {
        return false;
    }

    if ((value == node->data)) {
        return true;
    }

    if ((value < node->data)) {
        return contains_node(node->left, value);
    }

    return contains_node(node->right, value);
}

}  // namespace binary_search_tree
