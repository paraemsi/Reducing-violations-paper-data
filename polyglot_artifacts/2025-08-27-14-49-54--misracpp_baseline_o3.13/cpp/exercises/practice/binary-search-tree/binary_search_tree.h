#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

/*
 * A simple binary search tree that stores data of type T.
 * All interface and traversal functions are kept inline so that
 * template instantiation works without needing a separate .cpp file.
 */
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_{data} {}

    // Insert a value into the correct position in the tree.
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

    // Accessors used by the test-suite.
    const T& data()  const { return data_;          }
    const std::unique_ptr<binary_tree<T>>& left()  const noexcept { return left_;  }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    // Determine whether a value is already present in the tree.
    bool contains(const T& value) const {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    /*------------------------------------------------------------------
     * In-order iterator implementation so the tree can be used
     * directly in a range-based for loop.  The iterator keeps a stack
     * of nodes that still need to be visited.
     *----------------------------------------------------------------*/
    class iterator {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree* node) { push_left(node); }

        reference operator*()  const { return stack_.back()->data_; }
        pointer   operator->() const { return &(stack_.back()->data_); }

        iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const iterator& a, const iterator& b) {
            if (a.stack_.empty() && b.stack_.empty()) return true;
            if (a.stack_.empty() || b.stack_.empty()) return false;
            return a.stack_.back() == b.stack_.back();
        }
        friend bool operator!=(const iterator& a, const iterator& b) {
            return !(a == b);
        }

    private:
        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        std::vector<const binary_tree*> stack_;
    };

    iterator begin() const { return iterator(this); }
    iterator end()   const { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{nullptr};
    std::unique_ptr<binary_tree<T>> right_{nullptr};
};

/* Traversal helpers expected by the exercism test-suite. */
template <typename T>
std::vector<T> pre_order(const binary_tree<T>& tree) {
    std::vector<T> result{tree.data()};
    if (tree.left())  {
        auto v = pre_order(*tree.left());
        result.insert(result.end(), v.begin(), v.end());
    }
    if (tree.right()) {
        auto v = pre_order(*tree.right());
        result.insert(result.end(), v.begin(), v.end());
    }
    return result;
}

template <typename T>
std::vector<T> in_order(const binary_tree<T>& tree) {
    std::vector<T> result;
    if (tree.left()) {
        auto v = in_order(*tree.left());
        result.insert(result.end(), v.begin(), v.end());
    }
    result.push_back(tree.data());
    if (tree.right()) {
        auto v = in_order(*tree.right());
        result.insert(result.end(), v.begin(), v.end());
    }
    return result;
}

template <typename T>
std::vector<T> post_order(const binary_tree<T>& tree) {
    std::vector<T> result;
    if (tree.left()) {
        auto v = post_order(*tree.left());
        result.insert(result.end(), v.begin(), v.end());
    }
    if (tree.right()) {
        auto v = post_order(*tree.right());
        result.insert(result.end(), v.begin(), v.end());
    }
    result.push_back(tree.data());
    return result;
}

}  // namespace binary_search_tree

#endif  // BINARY_SEARCH_TREE_H
