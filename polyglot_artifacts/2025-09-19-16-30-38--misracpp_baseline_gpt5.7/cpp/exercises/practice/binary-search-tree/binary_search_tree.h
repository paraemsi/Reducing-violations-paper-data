#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : data_(value) {}

    // Insert a value into the tree (duplicates go to the left subtree).
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree(value));
            }
        }
    }

    const T& data() const noexcept { return data_; }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() noexcept : current_(nullptr) {}

        explicit const_iterator(const binary_tree* root) : current_(nullptr) {
            push_left(root);
            step();
        }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &current_->data_; }

        const_iterator& operator++() { step(); return *this; }
        const_iterator operator++(int) { const_iterator tmp(*this); step(); return tmp; }

        friend bool operator==(const const_iterator& a, const const_iterator& b) {
            return a.current_ == b.current_;
        }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) {
            return !(a == b);
        }

    private:
        const binary_tree* current_;
        std::stack<const binary_tree*> stack_;

        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push(node);
                node = node->left_.get();
            }
        }

        void step() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.top();
            stack_.pop();
            if (current_->right_) {
                push_left(current_->right_.get());
            }
        }
    };

    const_iterator begin() const noexcept { return const_iterator(this); }
    const_iterator end() const noexcept { return const_iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
