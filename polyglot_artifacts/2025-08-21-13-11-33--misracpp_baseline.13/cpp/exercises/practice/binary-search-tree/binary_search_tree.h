#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <stack>

namespace binary_search_tree {

template <typename T>
struct binary_tree {
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}

    const T& data() const { return data_; }
    binary_tree<T>* left() const { return left_.get(); }
    binary_tree<T>* right() const { return right_.get(); }

    // Insert value into the tree
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

    // Search for value in the tree
    bool search(const T& value) const {
        if (data_ == value) return true;
        if (value < data_) {
            return left_ ? left_->search(value) : false;
        } else {
            return right_ ? right_->search(value) : false;
        }
    }

    // In-order iterator
    struct iterator {
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(binary_tree<T>* root) {
            while (root) {
                stack_.push(root);
                root = root->left();
            }
            advance();
        }

        reference operator*() const { return current_->data(); }
        pointer operator->() const { return &(current_->data()); }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        binary_tree<T>* current_ = nullptr;
        std::stack<binary_tree<T>*> stack_;

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.top();
            stack_.pop();
            binary_tree<T>* node = current_->right();
            while (node) {
                stack_.push(node);
                node = node->left();
            }
        }
    };

    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }
    // const versions
    iterator begin() const { return iterator(const_cast<binary_tree<T>*>(this)); }
    iterator end() const { return iterator(); }
    using const_iterator = iterator;
    // For range-based for loops on const objects
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }
};

// Helper to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) return nullptr;
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
