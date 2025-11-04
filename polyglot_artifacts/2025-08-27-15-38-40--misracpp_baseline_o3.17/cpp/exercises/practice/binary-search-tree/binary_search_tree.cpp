#include "binary_search_tree.h"

namespace binary_search_tree {

void BinarySearchTree::insert(int value) {
  insert(root_, value);
}

bool BinarySearchTree::contains(int value) const {
  return contains(root_, value);
}

void BinarySearchTree::insert(BinarySearchTree::Node*& node, int value) {
  if (node == nullptr) {
    node = new Node(value);
  } else if (value <= node->data) {
    insert(node->left, value);
  } else {
    insert(node->right, value);
  }
}

bool BinarySearchTree::contains(const BinarySearchTree::Node* node, int value) {
  if (node == nullptr) {
    return false;
  }
  if (node->data == value) {
    return true;
  } else if (value < node->data) {
    return contains(node->left, value);
  } else {
    return contains(node->right, value);
  }
}

void BinarySearchTree::destroy(BinarySearchTree::Node* node) {
  if (node != nullptr) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

BinarySearchTree::~BinarySearchTree() {
  destroy(root_);
}

}  // namespace binary_search_tree
