#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>
#include <utility>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_(value) {}
    explicit binary_tree(T&& value) : value_(std::move(value)) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(binary_tree&&) = default;

    const T& data() const { return value_; }

    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    void insert(const T& v) {
        if (v <= value_) {
            if (left_) {
                left_->insert(v);
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(v));
            }
        } else {
            if (right_) {
                right_->insert(v);
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(v));
            }
        }
    }


    bool contains(const T& v) const {
        if (v == value_) return true;
        if (v < value_) return left_ ? left_->contains(v) : false;
        return right_ ? right_->contains(v) : false;
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        explicit iterator(const binary_tree* root) { push_left(root); }

        reference operator*() const { return stack_.top()->value_; }
        pointer operator->() const { return &(stack_.top()->value_); }

        iterator& operator++() {
            const binary_tree* node = stack_.top();
            stack_.pop();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& a, const iterator& b) {
            if (a.stack_.empty() && b.stack_.empty()) return true;
            if (a.stack_.empty() || b.stack_.empty()) return false;
            return a.stack_.top() == b.stack_.top();
        }

        friend bool operator!=(const iterator& a, const iterator& b) {
            return !(a == b);
        }

    private:
        std::stack<const binary_tree*> stack_;

        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T value_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
