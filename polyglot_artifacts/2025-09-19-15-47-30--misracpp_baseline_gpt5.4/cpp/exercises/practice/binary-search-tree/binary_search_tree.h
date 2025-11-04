#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace binary_search_tree {

// A generic binary search tree node that owns its subtrees.
// - Duplicates are inserted into the left subtree.
// - Provides read-only accessors for data/left/right.
// - Supports range-based for iteration (in-order traversal) via begin()/end().
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : value_(value) {}
    explicit binary_tree(T&& value) : value_(std::move(value)) {}

    void insert(const T& value) {
        invalidate_traversal();
        if (value <= value_) {
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
    }

    const T& data() const noexcept { return value_; }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    typename std::vector<T>::iterator begin() {
        ensure_traversal();
        return traversal_.begin();
    }
    typename std::vector<T>::iterator end() {
        ensure_traversal();
        return traversal_.end();
    }
    typename std::vector<T>::const_iterator begin() const {
        ensure_traversal();
        return traversal_.cbegin();
    }
    typename std::vector<T>::const_iterator end() const {
        ensure_traversal();
        return traversal_.cend();
    }

private:
    T value_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    // Cached in-order traversal to back range-based iteration.
    mutable std::vector<T> traversal_;

    void invalidate_traversal() const { traversal_.clear(); }

    void inorder_collect(std::vector<T>& out) const {
        if (left_) left_->inorder_collect(out);
        out.push_back(value_);
        if (right_) right_->inorder_collect(out);
    }

    void ensure_traversal() const {
        if (traversal_.empty()) {
            traversal_.reserve(size());
            inorder_collect(traversal_);
        }
    }

    std::size_t size() const noexcept {
        std::size_t s = 1;
        if (left_) s += left_->size();
        if (right_) s += right_->size();
        return s;
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
