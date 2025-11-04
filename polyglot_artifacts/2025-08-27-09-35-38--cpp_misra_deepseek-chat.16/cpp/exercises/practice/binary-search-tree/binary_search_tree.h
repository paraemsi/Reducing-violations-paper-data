#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <functional>
#include <stdexcept>

namespace binary_search_tree {

template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}
    
    // Insert a value
    void insert(T value);
    
    // Search for a value
    bool find(T value) const;
    
    // Get root data
    T data() const;
    
    // Get left subtree
    std::unique_ptr<BinarySearchTree<T>> left() const;
    
    // Get right subtree
    std::unique_ptr<BinarySearchTree<T>> right() const;
    
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    // Helper functions
    void insert(std::unique_ptr<Node>& node, T value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }
        
        if (value <= node->data) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }
    
    bool find(const std::unique_ptr<Node>& node, T value) const {
        if (!node) {
            return false;
        }
        
        if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return find(node->left, value);
        } else {
            return find(node->right, value);
        }
    }
};

template<typename T>
void BinarySearchTree<T>::insert(T value) {
    insert(root, value);
}

template<typename T>
bool BinarySearchTree<T>::find(T value) const {
    return find(root, value);
}

template<typename T>
T BinarySearchTree<T>::data() const {
    if (!root) {
        throw std::runtime_error("Tree is empty");
    }
    return root->data;
}

template<typename T>
std::unique_ptr<BinarySearchTree<T>> BinarySearchTree<T>::left() const {
    auto left_tree = std::make_unique<BinarySearchTree<T>>();
    if (root && root->left) {
        // Deep copy the left subtree
        std::function<std::unique_ptr<Node>(const std::unique_ptr<Node>&)> copy_tree;
        copy_tree = [&copy_tree](const std::unique_ptr<Node>& node) -> std::unique_ptr<Node> {
            if (!node) return nullptr;
            auto new_node = std::make_unique<Node>(node->data);
            new_node->left = copy_tree(node->left);
            new_node->right = copy_tree(node->right);
            return new_node;
        };
        left_tree->root = copy_tree(root->left);
    }
    return left_tree;
}

template<typename T>
std::unique_ptr<BinarySearchTree<T>> BinarySearchTree<T>::right() const {
    auto right_tree = std::make_unique<BinarySearchTree<T>>();
    if (root && root->right) {
        // Deep copy the right subtree
        std::function<std::unique_ptr<Node>(const std::unique_ptr<Node>&)> copy_tree;
        copy_tree = [&copy_tree](const std::unique_ptr<Node>& node) -> std::unique_ptr<Node> {
            if (!node) return nullptr;
            auto new_node = std::make_unique<Node>(node->data);
            new_node->left = copy_tree(node->left);
            new_node->right = copy_tree(node->right);
            return new_node;
        };
        right_tree->root = copy_tree(root->right);
    }
    return right_tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
