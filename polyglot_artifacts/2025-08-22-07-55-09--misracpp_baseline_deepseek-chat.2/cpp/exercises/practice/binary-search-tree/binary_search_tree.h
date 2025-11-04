#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <stack>
#include <cstddef>
#include <stdexcept>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    binary_tree(T value) : root(new Node(value)) {}
    ~binary_tree() {
        destroyTree(root);
    }
    
    void insert(T value) {
        insert(root, value);
    }
    
    bool contains(T value) const {
        return contains(root, value);
    }
    
    const T& data() const {
        // Add a check to prevent accessing nullptr
        if (root == nullptr) {
            // Handle error - for now, we'll throw an exception
            throw std::runtime_error("Data called on empty tree");
        }
        return root->data;
    }
    
    binary_tree* left() const {
        if (!root || !root->left) return nullptr;
        binary_tree* leftTree = new binary_tree(root->left->data);
        copySubtree(leftTree->root, root->left);
        return leftTree;
    }
    
    binary_tree* right() const {
        if (!root || !root->right) return nullptr;
        binary_tree* rightTree = new binary_tree(root->right->data);
        copySubtree(rightTree->root, root->right);
        return rightTree;
    }

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    void insert(Node*& node, T value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value <= node->data) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }
    
    bool contains(Node* node, T value) const {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data) {
            return contains(node->left, value);
        } else {
            return contains(node->right, value);
        }
    }
    
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    // Helper function to recursively copy a subtree
    void copySubtree(Node*& dest, Node* src) const {
        if (!src) return;
        // The root node is already created, so we only need to handle children
        if (src->left) {
            dest->left = new Node(src->left->data);
            copySubtree(dest->left, src->left);
        }
        if (src->right) {
            dest->right = new Node(src->right->data);
            copySubtree(dest->right, src->right);
        }
    }
    
    // Iterator support
    // We need to provide begin() and end() for range-based for loops
    // Let's implement an in-order iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator(Node* node = nullptr) : current(nullptr) {
            // Traverse to the leftmost node
            while (node) {
                stack.push(node);
                node = node->left;
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
        }
        
        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }
        
        iterator& operator++() {
            // Move to next node in in-order traversal
            // Make sure current is valid
            if (current) {
                if (current->right) {
                    Node* node = current->right;
                    while (node) {
                        stack.push(node);
                        node = node->left;
                    }
                }
                if (stack.empty()) {
                    current = nullptr;
                } else {
                    current = stack.top();
                    stack.pop();
                }
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
        
    private:
        Node* current;
        std::stack<Node*> stack;
    };
    
    iterator begin() const {
        return iterator(root);
    }
    
    iterator end() const {
        return iterator(nullptr);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
