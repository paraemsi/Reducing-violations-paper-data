#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_(value) {}
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(binary_tree&&) = default;

    // Accessors
    const T& data() const { return value_; }
    const binary_tree* left() const { return left_.get(); }
    const binary_tree* right() const { return right_.get(); }

    // Insert a value into this tree (duplicates go to the left subtree)
    void insert(const T& value) {
        if (value <= value_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            }
        }
    }

    // In-order iterator yielding values in non-decreasing order.
    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() : current_(nullptr) {}
        explicit iterator(const binary_tree* root) : current_(nullptr) {
            push_left(root);
            advance();
        }

        reference operator*() const { return current_->data(); }
        pointer operator->() const { return &current_->data(); }

        iterator& operator++() {
            if (!current_) return *this;
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right()) {
                push_left(node->right());
            }
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const { return current_ == other.current_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        const binary_tree* current_;
        std::vector<const binary_tree*> stack_;

        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left();
            }
        }

        void advance() {
            current_ = stack_.empty() ? nullptr : stack_.back();
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T value_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

// Helper to build a tree from an initializer_list
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> values) {
    std::unique_ptr<binary_tree<T>> root;
    for (const auto& v : values) {
        if (!root) {
            root.reset(new binary_tree<T>(v));
        } else {
            root->insert(v);
        }
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
