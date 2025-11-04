#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    typedef std::unique_ptr<binary_tree<T>> node_ptr;

    explicit binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    // Insert a value into the tree
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            }
        }
    }

    // Search for a value in the tree
    bool search(const T& value) const {
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return left_ ? left_->search(value) : false;
        } else {
            return right_ ? right_->search(value) : false;
        }
    }

    // Accessors for test code
    const T& data() const { return data_; }
    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }

    // Iterator for in-order traversal
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr), started_(false) {}

        explicit iterator(const binary_tree<T>* root) : current_(root), started_(false) {
            if (root != nullptr) {
                push_left(current_);
                advance();
            } else {
                current_ = nullptr;
                started_ = true;
            }
        }

        reference operator*() const { return current_value_; }
        pointer operator->() const { return &current_value_; }

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
            return (stack_ == other.stack_) && (current_ == other.current_) && (started_ == other.started_);
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

        void advance() {
            if (!started_) {
                started_ = true;
                if (!stack_.empty()) {
                    const binary_tree<T>* node = stack_.back();
                    stack_.pop_back();
                    current_value_ = node->data_;
                    push_left(node->right_.get());
                } else {
                    current_ = nullptr;
                }
                return;
            }
            if (!stack_.empty()) {
                const binary_tree<T>* node = stack_.back();
                stack_.pop_back();
                current_value_ = node->data_;
                push_left(node->right_.get());
            } else {
                current_ = nullptr;
            }
        }

        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;
        T current_value_{};
        bool started_;
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(nullptr); }

private:
    T data_;
    node_ptr left_;
    node_ptr right_;
};

// Helper to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (std::size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
