#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <vector>
#include <functional>
#include <string>
#include <stdexcept>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    explicit binary_tree(const T& data) : root(new Node(data)) {}
    
    // Insert a value into the tree
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    // Search for a value in the tree
    bool find(const T& value) const {
        return find(root, value);
    }
    
    // Get the root node's data
    T data() const {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        return root->data;
    }
    
    // Get left and right subtrees
    binary_tree left() const {
        if (root && root->left) {
            return binary_tree(root->left);
        }
        return binary_tree();
    }
    
    binary_tree right() const {
        if (root && root->right) {
            return binary_tree(root->right);
        }
        return binary_tree();
    }
    
    // In-order traversal
    std::vector<T> in_order_traversal() const {
        std::vector<T> result;
        in_order_traversal(root, result);
        return result;
    }
    
    // Begin and end for iteration
    auto begin() const {
        auto traversal = in_order_traversal();
        return traversal.begin();
    }
    
    auto end() const {
        auto traversal = in_order_traversal();
        return traversal.end();
    }
    
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    binary_tree(Node* node) : root(node) {}
    
    Node* insert(Node* node, const T& value) {
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
    
    bool find(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        if (value < node->data) {
            return find(node->left, value);
        } else {
            return find(node->right, value);
        }
    }
    
    void in_order_traversal(Node* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        in_order_traversal(node->left, result);
        result.push_back(node->data);
        in_order_traversal(node->right, result);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
