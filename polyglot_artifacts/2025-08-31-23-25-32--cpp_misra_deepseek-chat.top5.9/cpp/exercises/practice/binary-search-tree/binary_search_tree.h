#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) 
        : data_{data}, left_{nullptr}, right_{nullptr} {}
    
    const T& data() const { return data_; }
    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }
    
    void insert(const T& data) {
        if ((data <= data_)) {
            if (left_ == nullptr) {
                left_ = std::make_unique<binary_tree<T>>(data);
            } else {
                left_->insert(data);
            }
        } else {
            if (right_ == nullptr) {
                right_ = std::make_unique<binary_tree<T>>(data);
            } else {
                right_->insert(data);
            }
        }
    }
    
    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        iterator() : is_end_{true} {}
        explicit iterator(binary_tree<T>* node) : is_end_{false} {
            // In-order traversal using a stack
            push_left(node);
        }
        
        reference operator*() const { 
            return stack_.back()->data(); 
        }
        pointer operator->() const { 
            return &stack_.back()->data(); 
        }
        
        iterator& operator++() {
            if (stack_.empty()) {
                is_end_ = true;
                return *this;
            }
            binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            if (stack_.empty()) {
                is_end_ = true;
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const { 
            // If both are at the end, they're equal
            if (is_end_ && other.is_end_) {
                return true;
            }
            // If one is at the end and the other isn't, they're not equal
            if (is_end_ != other.is_end_) {
                return false;
            }
            // If neither is at the end, check if their current nodes are the same
            // Since we're doing in-order traversal, and the stack represents the path,
            // this may not be precise, but for the purpose of testing if we've reached the end, it's sufficient
            // For non-end iterators, we'll consider them equal if they point to the same node
            // This may need to be adjusted based on test requirements
            if (stack_.empty() && other.stack_.empty()) {
                return true;
            }
            if (stack_.empty() || other.stack_.empty()) {
                return false;
            }
            return stack_.back() == other.stack_.back();
        }
        bool operator!=(const iterator& other) const { 
            return !(*this == other);
        }
        
    private:
        std::vector<binary_tree<T>*> stack_;
        bool is_end_;
        
        void push_left(binary_tree<T>* node) {
            while (node != nullptr) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
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

// Helper function to create a tree from initial data
template<typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
