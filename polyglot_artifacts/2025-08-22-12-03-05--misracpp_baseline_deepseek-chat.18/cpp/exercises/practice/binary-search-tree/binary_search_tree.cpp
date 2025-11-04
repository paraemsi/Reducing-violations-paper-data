#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(int value) {
    root = insert(root, value);
}

Node* BinarySearchTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }
    
    if (value <= node->data) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
    return node;
}

Node* BinarySearchTree::find(int value) const {
    return find(root, value);
}

Node* BinarySearchTree::find(Node* node, int value) const {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (node->data == value) {
        return node;
    } else if (value < node->data) {
        return find(node->left, value);
    } else {
        return find(node->right, value);
    }
}

}  // namespace binary_search_tree
