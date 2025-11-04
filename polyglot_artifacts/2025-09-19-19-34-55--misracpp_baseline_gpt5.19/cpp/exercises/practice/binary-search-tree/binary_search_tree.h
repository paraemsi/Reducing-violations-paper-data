#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

// A generic binary search tree that supports insert and search.
// Duplicates are inserted into the left subtree.
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_(data) {}

    const T& data() const { return data_; }

    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    // Forward declare iterator and grant access to private members.
    class const_iterator;
    friend class const_iterator;

    // Iterator to traverse the tree in-order.
    class const_iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : current_(nullptr) {}
        explicit const_iterator(const binary_tree<T>* root) {
            push_left(root);
            pop_to_current();
        }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &current_->data_; }

        const_iterator& operator++() {
            advance();
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            advance();
            return tmp;
        }

        bool operator==(const const_iterator& other) const { return current_ == other.current_; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }

    private:
        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        void pop_to_current() {
            if (!stack_.empty()) {
                current_ = stack_.back();
                stack_.pop_back();
            } else {
                current_ = nullptr;
            }
        }
        void advance() {
            if (!current_) return;
            if (current_->right_) {
                push_left(current_->right_.get());
            }
            pop_to_current();
        }

        const binary_tree<T>* current_{nullptr};
        std::vector<const binary_tree<T>*> stack_{};
    };
    
    // Grant iterator access to private members moved above.

    // Non-const and const begin/end to support range-based for on mutable and const trees.
    using iterator = const_iterator;
    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }
    const_iterator begin() const { return const_iterator(this); }
    const_iterator end() const { return const_iterator(); }

    binary_tree<T>& insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_.reset(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_.reset(new binary_tree<T>(value));
            }
        }
        return *this;
    }

    bool contains(const T& value) const {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // In-order traversal returning sorted values.
    std::vector<T> as_vector() const {
        std::vector<T> out;
        in_order_traverse(out);
        return out;
    }

private:
    void in_order_traverse(std::vector<T>& out) const {
        if (left_) {
            left_->in_order_traverse(out);
        }
        out.push_back(data_);
        if (right_) {
            right_->in_order_traverse(out);
        }
    }

    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
