#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : data_(value) {}
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    const T& data() const { return data_; }

    // Insert a value into the tree.
    // Values less than or equal to the current node go to the left subtree.
    void insert(const T& value) {
        cache_valid_ = false;
        binary_tree<T>* curr = this;
        while (true) {
            if (value <= curr->data_) {
                if (curr->left_) {
                    curr = curr->left_.get();
                } else {
                    curr->left_.reset(new binary_tree<T>(value));
                    return;
                }
            } else {
                if (curr->right_) {
                    curr = curr->right_.get();
                } else {
                    curr->right_.reset(new binary_tree<T>(value));
                    return;
                }
            }
        }
    }

    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const {
        ensure_cache();
        return cache_.cbegin();
    }

    const_iterator end() const {
        ensure_cache();
        return cache_.cend();
    }

private:
    void inorder_traverse(const binary_tree<T>* node) const {
        if (!node) return;
        inorder_traverse(node->left_.get());
        cache_.push_back(node->data_);
        inorder_traverse(node->right_.get());
    }

    void ensure_cache() const {
        if (!cache_valid_) {
            cache_.clear();
            inorder_traverse(this);
            cache_valid_ = true;
        }
    }

    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    // Mutable cache for iteration in sorted (in-order) sequence
    mutable std::vector<T> cache_;
    mutable bool cache_valid_ = false;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
