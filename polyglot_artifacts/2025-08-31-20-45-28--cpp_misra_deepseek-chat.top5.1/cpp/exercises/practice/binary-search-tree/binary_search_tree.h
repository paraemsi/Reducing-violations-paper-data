#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : valid_(false), data_{}, left_(nullptr), right_(nullptr) {}
    
    // Insert a value into the tree
    void insert(T value) {
        if (!valid_) {
            data_ = value;
            valid_ = true;
            return;
        }
        
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_.reset(new binary_tree(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_.reset(new binary_tree(value));
            }
        }
    }
    
    // Check if the tree contains a value
    bool contains(T value) const {
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return left_ ? left_->contains(value) : false;
        } else {
            return right_ ? right_->contains(value) : false;
        }
    }
    
    // Accessors
    const T& data() const {
        if (!valid_) {
            throw std::runtime_error("Accessing data of an empty tree");
        }
        return data_;
    }
    
    const binary_tree* left() const {
        return left_.get();
    }
    
    const binary_tree* right() const {
        return right_.get();
    }
    
    // Iterator support
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        iterator() : current(nullptr) {}
        explicit iterator(const binary_tree* node) {
            if (node == nullptr || !node->valid_) {
                current = nullptr;
                return;
            }
            // Push all left nodes to the stack
            const binary_tree* temp = node;
            while (temp != nullptr) {
                nodeStack.push(temp);
                temp = temp->left_.get();
            }
            advance();
        }
        
        T operator*() const {
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->data_;
        }
        
        iterator& operator++() {
            advance();
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            advance();
            return tmp;
        }
        
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        
    private:
        std::stack<const binary_tree*> nodeStack;
        const binary_tree* current;
        
        void advance() {
            if (nodeStack.empty()) {
                current = nullptr;
                return;
            }
            
            current = nodeStack.top();
            nodeStack.pop();
            
            // Push the right child's left subtree
            const binary_tree* temp = current->right_.get();
            while (temp != nullptr) {
                nodeStack.push(temp);
                temp = temp->left_.get();
            }
        }
    };
    
    iterator begin() const {
        if (!valid_) {
            return iterator();
        }
        return iterator(this);
    }
    
    iterator end() const {
        return iterator();
    }
    
private:
    explicit binary_tree(T value) : valid_(true), data_(value), left_(nullptr), right_(nullptr) {}
    
    bool valid_;
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    
    // Make the factory function a friend to access private constructor
    template <typename U>
    friend std::unique_ptr<binary_tree<U>> make_tree(const std::vector<U>& data);
};

// Factory function to create a tree from a list of values
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) {
        return nullptr;
    }
    auto tree = std::make_unique<binary_tree<T>>();
    // Set the root's data to the first element
    // Since data_ is private, we need to find a way to set it
    // Let's use the insert method
    // To do this, we need to make sure the first insert sets the root's data
    // We'll need to modify our implementation
    for (const auto& value : data) {
        tree->insert(value);
    }
    return tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
