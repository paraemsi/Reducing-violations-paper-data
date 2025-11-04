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
    binary_tree(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    const T& data() const { return data_; }
    const binary_tree<T>* left() const { return left_.get(); }
    binary_tree<T>* left() { return left_.get(); }
    const binary_tree<T>* right() const { return right_.get(); }
    binary_tree<T>* right() { return right_.get(); }
    
    void insert(const T& value) {
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
    
    // Iterator class for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(binary_tree<T>* root) {
            // Push all left nodes to the stack
            current = root;
            while (current) {
                node_stack.push(current);
                current = current->left_.get();
            }
            if (!node_stack.empty()) {
                current = node_stack.top();
                node_stack.pop();
            }
        }
        
        reference operator*() const { return current->data_; }
        pointer operator->() const { return &current->data_; }
        
        iterator& operator++() {
            // Move to the next node in in-order traversal
            if (current->right_) {
                current = current->right_.get();
                while (current) {
                    node_stack.push(current);
                    current = current->left_.get();
                }
            }
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

template <typename T>
std::unique_ptr<binary_tree<T>> build_tree(const std::vector<T>& values) {
    if (values.empty()) return nullptr;
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

// Alias to match the test's expected name
template <typename T>
using tree_ptr = std::unique_ptr<binary_tree<T>>;

template <typename T>
tree_ptr<T> make_tree(const std::vector<T>& values) {
    return build_tree(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
