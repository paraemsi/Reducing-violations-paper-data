#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

/*
 * A simple binary search tree that stores comparable data.
 *
 * The tree obeys the binary-search-tree invariant:
 *   - Values less than or equal to the current node’s data live in the left
 *     subtree.
 *   - Values greater than the current node’s data live in the right subtree.
 *
 * All operations run in O(h) where h is the height of the tree.
 */
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data);

    // Non-const and const accessors for the left / right sub-trees.
    std::unique_ptr<binary_tree<T>>& left();
    const std::unique_ptr<binary_tree<T>>& left() const;

    std::unique_ptr<binary_tree<T>>& right();
    const std::unique_ptr<binary_tree<T>>& right() const;

    // Insert a value into the tree, preserving BST ordering.
    void insert(const T& value);

    // Data stored at this node.
    const T& data() const;

    // Return the contents of the entire tree in sorted (in-order) form.
    std::vector<T> sorted_data() const;

    // STL-style traversal support (in-order).
    typename std::vector<T>::const_iterator begin();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end();
    typename std::vector<T>::const_iterator end() const;

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    // Cache used for supplying iterators.
    mutable std::vector<T> traversal_cache_;
};

/* ------------------------------------------------------------------ */
/*                            Implementation                          */
/* ------------------------------------------------------------------ */

template <typename T>
binary_tree<T>::binary_tree(const T& data)
    : data_{data}, left_{nullptr}, right_{nullptr} {}

template <typename T>
std::unique_ptr<binary_tree<T>>& binary_tree<T>::left() { return left_; }

template <typename T>
const std::unique_ptr<binary_tree<T>>& binary_tree<T>::left() const { return left_; }

template <typename T>
std::unique_ptr<binary_tree<T>>& binary_tree<T>::right() { return right_; }

template <typename T>
const std::unique_ptr<binary_tree<T>>& binary_tree<T>::right() const { return right_; }

template <typename T>
void binary_tree<T>::insert(const T& value) {
    traversal_cache_.clear();
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

template <typename T>
const T& binary_tree<T>::data() const { return data_; }

template <typename T>
std::vector<T> binary_tree<T>::sorted_data() const {
    std::vector<T> result;
    if (left_) {
        auto left_vec = left_->sorted_data();
        result.insert(result.end(), left_vec.begin(), left_vec.end());
    }
    result.push_back(data_);
    if (right_) {
        auto right_vec = right_->sorted_data();
        result.insert(result.end(), right_vec.begin(), right_vec.end());
    }
    return result;
}

template <typename T>
typename std::vector<T>::const_iterator binary_tree<T>::begin() {
    traversal_cache_ = sorted_data();
    return traversal_cache_.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator binary_tree<T>::begin() const {
    traversal_cache_ = sorted_data();
    return traversal_cache_.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator binary_tree<T>::end() {
    traversal_cache_ = sorted_data();
    return traversal_cache_.cend();
}

template <typename T>
typename std::vector<T>::const_iterator binary_tree<T>::end() const {
    traversal_cache_ = sorted_data();
    return traversal_cache_.cend();
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
