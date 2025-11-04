#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stdexcept>

namespace binary_search_tree {

template <typename T>
class binary_tree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(const T& item) : data(item), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
public:
    binary_tree() = default;
    explicit binary_tree(const T& data) {
        root = std::make_unique<Node>(data);
    }
private:
    explicit binary_tree(std::unique_ptr<Node> node) : root(std::move(node)) {}
public:
    
    // Insert a new item into the tree
    void insert(const T& item) {
        if (!root) {
            root = std::make_unique<Node>(item);
            return;
        }
        insert_helper(root.get(), item);
    }
    
    // Check if an item exists in the tree
    bool contains(const T& item) const {
        return contains_helper(root.get(), item);
    }
    
    // Get the root data
    const T& data() const {
        if (!root) {
            throw std::runtime_error("Tree is empty");
        }
        return root->data;
    }
    
    // Get left and right subtrees
    std::unique_ptr<binary_tree> left() const {
        if (root && root->left) {
            return std::make_unique<binary_tree>(copy_tree(root->left.get()));
        }
        return nullptr;
    }
    
    std::unique_ptr<binary_tree> right() const {
        if (root && root->right) {
            return std::make_unique<binary_tree>(copy_tree(root->right.get()));
        }
        return nullptr;
    }

private:
    void insert_helper(Node* node, const T& item) {
        if (item <= node->data) {
            if (node->left) {
                insert_helper(node->left.get(), item);
            } else {
                node->left = std::make_unique<Node>(item);
            }
        } else {
            if (node->right) {
                insert_helper(node->right.get(), item);
            } else {
                node->right = std::make_unique<Node>(item);
            }
        }
    }
    
    bool contains_helper(const Node* node, const T& item) const {
        if (!node) return false;
        if (item == node->data) return true;
        if (item < node->data) {
            return contains_helper(node->left.get(), item);
        } else {
            return contains_helper(node->right.get(), item);
        }
    }
    
    // Helper function to recursively copy the tree
    std::unique_ptr<Node> copy_tree(const Node* node) const {
        if (!node) return nullptr;
        auto new_node = std::make_unique<Node>(node->data);
        new_node->left = copy_tree(node->left.get());
        new_node->right = copy_tree(node->right.get());
        return new_node;
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
