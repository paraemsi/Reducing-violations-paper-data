#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <stack>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(T value) {
        if (root == nullptr) {
            root = std::make_unique<TreeNode>(value);
            return;
        }
        
        TreeNode* current = root.get();
        while (true) {
            if ((value <= current->data)) {
                if (current->left != nullptr) {
                    current = current->left.get();
                } else {
                    current->left = std::make_unique<TreeNode>(value);
                    break;
                }
            } else {
                if (current->right != nullptr) {
                    current = current->right.get();
                } else {
                    current->right = std::make_unique<TreeNode>(value);
                    break;
                }
            }
        }
    }
    
    bool contains(T value) const {
        const TreeNode* current = root.get();
        while (current != nullptr) {
            if ((value == current->data)) {
                return true;
            } else if ((value < current->data)) {
                current = current->left.get();
            } else {
                current = current->right.get();
            }
        }
        return false;
    }
    
    const T* data() const {
        if (!root) return nullptr;
        return &root->data;
    }
    
    binary_tree<T>* left() const {
        if (!root || !root->left) return nullptr;
        binary_tree<T>* leftTree = new binary_tree<T>();
        leftTree->root = std::make_unique<TreeNode>(*(root->left));
        return leftTree;
    }
    
    binary_tree<T>* right() const {
        if (!root || !root->right) return nullptr;
        binary_tree<T>* rightTree = new binary_tree<T>();
        rightTree->root = std::make_unique<TreeNode>(*(root->right));
        return rightTree;
    }

private:
    struct TreeNode {
        T data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        
        explicit TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
        // Copy constructor for deep copy
        TreeNode(const TreeNode& other)
            : data(other.data),
              left(other.left ? std::make_unique<TreeNode>(*other.left) : nullptr),
              right(other.right ? std::make_unique<TreeNode>(*other.right) : nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    
    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        
        reference operator*() const { return current->data; }
        pointer operator->() { return &current->data; }
        
        // Prefix increment
        iterator& operator++() {
            if (stack.empty()) {
                current = nullptr;
                return *this;
            }
            
            // The current node is the one we're moving away from
            // Get the next node from the stack
            TreeNode* node = stack.top();
            stack.pop();
            
            // If this node has a right child, push the left path of the right subtree
            if (node->right != nullptr) {
                TreeNode* temp = node->right.get();
                while (temp != nullptr) {
                    stack.push(temp);
                    temp = temp->left.get();
                }
            }
            
            // Set current to the next node to process (if any)
            if (stack.empty()) {
                current = nullptr;
            } else {
                current = stack.top();
            }
            return *this;
        }
        
        // Postfix increment
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        friend bool operator== (const iterator& a, const iterator& b) { 
            return a.current == b.current;
        }
        friend bool operator!= (const iterator& a, const iterator& b) { 
            return a.current != b.current;
        }
        
    private:
        TreeNode* current;
        std::stack<TreeNode*> stack;
        
        // Helper function to push all left nodes onto the stack
        void push_left(TreeNode* node) {
            while (node != nullptr) {
                stack.push(node);
                node = node->left.get();
            }
        }
        
        // Private constructor for begin()
        iterator(TreeNode* root) {
            if (root == nullptr) {
                current = nullptr;
                return;
            }
            // Push all left nodes to initialize the stack
            TreeNode* node = root;
            while (node != nullptr) {
                stack.push(node);
                node = node->left.get();
            }
            // The current is the top of the stack (first element)
            // But we need to set current to the first element to return
            // The stack.top() is the first element, which we'll process
            current = stack.top();
            // Note: We don't pop it here, as it needs to be returned when dereferenced
        }
        
        friend class binary_tree;
    };
    
    iterator begin() {
        return iterator(root.get());
    }
    
    iterator end() {
        return iterator();
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
