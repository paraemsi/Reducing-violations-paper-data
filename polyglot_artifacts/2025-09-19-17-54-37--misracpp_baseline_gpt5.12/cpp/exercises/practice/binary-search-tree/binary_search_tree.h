#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using const_iterator = typename std::vector<T>::const_iterator;
    using iterator = typename std::vector<T>::const_iterator;

    explicit binary_tree(const T& value) : data_{value} {}

    // Accessors
    const T& data() const { return data_; }

    std::unique_ptr<binary_tree<T>>& left() { return left_; }
    std::unique_ptr<binary_tree<T>>& right() { return right_; }
    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    // Insert a value into the tree. Values equal to the node's value go to the left subtree.
    void insert(const T& value) {
        traversal_dirty_ = true;
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
    }

    // Iteration (in-order traversal)
    iterator begin() {
        ensure_traversal();
        return traversal_.cbegin();
    }
    iterator end() {
        ensure_traversal();
        return traversal_.cend();
    }

    const_iterator begin() const {
        ensure_traversal();
        return traversal_.cbegin();
    }

    const_iterator end() const {
        ensure_traversal();
        return traversal_.cend();
    }

private:
    void fill_in_order(std::vector<T>& out) const {
        if (left_) {
            left_->fill_in_order(out);
        }
        out.push_back(data_);
        if (right_) {
            right_->fill_in_order(out);
        }
    }

    std::size_t size() const {
        std::size_t n = 1;
        if (left_) n += left_->size();
        if (right_) n += right_->size();
        return n;
    }

    void ensure_traversal() const {
        if (traversal_dirty_) {
            traversal_.clear();
            traversal_.reserve(size());
            fill_in_order(traversal_);
            traversal_dirty_ = false;
        }
    }

    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};

    // Cache for iteration
    mutable std::vector<T> traversal_;
    mutable bool traversal_dirty_ = true;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
