#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}
    
    void insert(int value) {
        root = insert(root, value);
    }
    
    Node* find(int value) const {
        return find(root, value);
    }
    
    Node* get_root() const { return root; }

private:
    Node* root;
    
    Node* insert(Node* node, int value) {
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
    
    Node* find(Node* node, int value) const {
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
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
