#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <stack>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    class Node {
    public:
        Node(T value) : data_(value), left_(nullptr), right_(nullptr) {}
        
        T data() const { return data_; }
        std::unique_ptr<Node>& left() { return left_; }
        std::unique_ptr<Node>& right() { return right_; }
        const std::unique_ptr<Node>& left() const { return left_; }
        const std::unique_ptr<Node>& right() const { return right_; }
        
    private:
        T data_;
        std::unique_ptr<Node> left_;
        std::unique_ptr<Node> right_;
    };
    
    binary_tree() : root_(nullptr) {}
    
    void insert(T data) {
        insert(root_, data);
    }
    
    const std::unique_ptr<Node>& root() const {
        return root_;
    }
    
    // Iterator support
    class iterator {
    public:
        iterator() : current_(nullptr) {}
        iterator(Node* root) : current_(nullptr) {
            if (root) {
                // Push all left nodes to reach the smallest element
                Node* node = root;
                while (node) {
                    stack_.push(node);
                    node = node->left().get();
                }
                if (!stack_.empty()) {
                    current_ = stack_.top();
                    stack_.pop();
                }
            }
        }
        
        T operator*() const { 
            // Ensure current_ is not nullptr before dereferencing
            if (!current_) {
                // Handle error - for now, return a default value
                // In a real implementation, you might want to throw an exception
                return T();
            }
            return current_->data(); 
        }
        iterator& operator++() {
            if (current_ && current_->right()) {
                Node* node = current_->right().get();
                while (node) {
                    stack_.push(node);
                    node = node->left().get();
                }
            }
            if (stack_.empty()) {
                current_ = nullptr;
            } else {
                current_ = stack_.top();
                stack_.pop();
            }
            return *this;
        }
        bool operator!=(const iterator& other) const { 
            return current_ != other.current_; 
        }
        
    private:
        Node* current_;
        std::stack<Node*> stack_;
    };
    
    iterator begin() {
        return iterator(root_.get());
    }
    
    iterator end() {
        return iterator();
    }
    
private:
    std::unique_ptr<Node> root_;
    
    void insert(std::unique_ptr<Node>& node, T data) {
        if (!node) {
            node = std::make_unique<Node>(data);
        } else if (data <= node->data()) {
            insert(node->left(), data);
        } else {
            insert(node->right(), data);
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
