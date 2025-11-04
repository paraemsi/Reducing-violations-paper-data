#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <string>
#include <stack>
#include <iterator>
#include <vector>

namespace binary_search_tree {

template <typename T>
class TreeNode {
private:
    T data_;
    TreeNode<T>* left_;
    TreeNode<T>* right_;
public:
    TreeNode(T value) : data_(value), left_(nullptr), right_(nullptr) {}
    
    T data() const {
        return data_;
    }
    
    TreeNode<T>* left() const {
        return left_;
    }
    
    TreeNode<T>* right() const {
        return right_;
    }
    
    // Make binary_tree a friend so it can access private members
    template <typename U>
    friend class binary_tree;
};

template <typename T>
class binary_tree {
private:
    TreeNode<T>* root;
    
    TreeNode<T>* insert(TreeNode<T>* node, T value);
    TreeNode<T>* find(TreeNode<T>* node, T value) const;
    
    // Helper function for in-order traversal
    void in_order_traversal(TreeNode<T>* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        in_order_traversal(node->left_, result);
        result.push_back(node->data_);
        in_order_traversal(node->right_, result);
    }
    
public:
    binary_tree() : root(nullptr) {}
    explicit binary_tree(T value) : root(new TreeNode<T>(value)) {}
    
    void insert(T value);
    TreeNode<T>* find(T value) const;
    TreeNode<T>* get_root() const { return root; }
    
    // Iterator support
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    private:
        std::stack<TreeNode<T>*> nodeStack;
        TreeNode<T>* current;
        
        void push_left(TreeNode<T>* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = node->left_;
            }
        }
        
    public:
        iterator(TreeNode<T>* root) {
            push_left(root);
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
                push_left(current->right_);
            } else {
                current = nullptr;
            }
        }
        
        iterator() : current(nullptr) {}
        
        T operator*() const {
            return current->data_;
        }
        
        iterator& operator++() {
            if (nodeStack.empty()) {
                current = nullptr;
            } else {
                current = nodeStack.top();
                nodeStack.pop();
                push_left(current->right_);
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };
    
    iterator begin() const {
        return iterator(root);
    }
    
    iterator end() const {
        return iterator();
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
