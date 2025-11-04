#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Iterator class to support range-based for loops
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(const binary_tree<T>* root) : current(nullptr) {
            if (root == nullptr) return;
            
            // Push all left nodes to reach the smallest element
            const binary_tree<T>* node = root;
            while (node) {
                nodeStack.push(node);
                node = node->left_.get();
            }
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
                // Prepare the next node
                const binary_tree<T>* temp = current->right_.get();
                while (temp) {
                    nodeStack.push(temp);
                    temp = temp->left_.get();
                }
            }
        }
        
        reference operator*() const {
            return current->data_;
        }
        
        pointer operator->() const {
            return &(current->data_);
        }
        
        iterator& operator++() {
            if (nodeStack.empty()) {
                current = nullptr;
                return *this;
            }
            
            current = nodeStack.top();
            nodeStack.pop();
            
            // Push the right subtree's leftmost path
            const binary_tree<T>* temp = current->right_.get();
            while (temp) {
                nodeStack.push(temp);
                temp = temp->left_.get();
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
        const binary_tree<T>* current;
        std::stack<const binary_tree<T>*> nodeStack;
    };
    
    explicit binary_tree(T value) : data_(value), left_(nullptr), right_(nullptr) {}
    
    void insert(T value) {
        if (value <= data_) {
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
    
    bool find(T value) const {
        if (value == data_) {
            return true;
        } else if (value <= data_) {
            return left_ && left_->find(value);
        } else {
            return right_ && right_->find(value);
        }
    }
    
    const binary_tree<T>* left() const {
        return left_.get();
    }
    
    const binary_tree<T>* right() const {
        return right_.get();
    }
    
    T data() const {
        return data_;
    }
    
    // Begin and end for iteration
    iterator begin() const {
        return iterator(this);
    }
    
    iterator end() const {
        return iterator();
    }
    
private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
