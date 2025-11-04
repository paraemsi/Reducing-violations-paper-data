#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <cstdint>
#include <iterator>
#include <stack>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    explicit binary_tree(T data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    T data() const { return data_; }
    std::unique_ptr<binary_tree<T>>& left() { return left_; }
    std::unique_ptr<binary_tree<T>>& right() { return right_; }
    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }
    
    void insert(T value) {
        if ((value <= data_)) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }
    
    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(binary_tree<T>* root) {
            // Push all left nodes to the stack
            current = nullptr;
            while (root != nullptr) {
                node_stack.push(root);
                root = (root->left_).get();
            }
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            }
        }
        
        T& operator*() { return current->data_; }
        T* operator->() { return &current->data_; }
        
        iterator& operator++() {
            // Move to the next node in in-order traversal
            if (current == nullptr) {
                return *this;
            }
            
            // Process the right subtree
            if ((current->right_) != nullptr) {
                binary_tree<T>* node = (current->right_).get();
                while (node != nullptr) {
                    node_stack.push(node);
                    node = (node->left_).get();
                }
            }
            
            // Get the next node from the stack
            if (node_stack.empty()) {
                current = nullptr;
            } else {
                current = node_stack.top();
                node_stack.pop();
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
        
    private:
        binary_tree<T>* current;
        std::stack<binary_tree<T>*> node_stack;
    };
    
    iterator begin() {
        return iterator(this);
    }
    
    iterator end() {
        return iterator();
    }
    
private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

// Helper function to create a tree from a list of values
template<typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (std::size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
