#include "binary_search_tree.h"

namespace binary_search_tree {

/*  Recursively insert, sending duplicates to the left as per specification. */
void insert(Node*& root, int value) {
    if (!root) {
        root = new Node(value);
        return;
    }
    if (value <= root->data) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}

bool contains(const Node* root, int value) {
    if (!root) {
        return false;
    }
    if (root->data == value) {
        return true;
    }
    return value < root->data ? contains(root->left, value)
                              : contains(root->right, value);
}

}  // namespace binary_search_tree
