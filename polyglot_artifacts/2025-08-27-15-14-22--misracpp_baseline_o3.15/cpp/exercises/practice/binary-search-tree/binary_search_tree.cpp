#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(int value) {
    insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return contains(root_, value);
}

BinarySearchTree::~BinarySearchTree() {
    destroy(root_);
}

void BinarySearchTree::insert(Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return;
    }
    if (value <= node->data) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

bool BinarySearchTree::contains(const Node* node, int value) {
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

void BinarySearchTree::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

}  // namespace binary_search_tree
