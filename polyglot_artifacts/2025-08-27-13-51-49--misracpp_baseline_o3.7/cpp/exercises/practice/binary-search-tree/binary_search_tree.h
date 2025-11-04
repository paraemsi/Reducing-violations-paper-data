#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Construct a tree node with the given value.
    explicit binary_tree(const T& value) : data_{value} {}

    // Return a reference to the value stored at this node.
    const T& data() const noexcept { return data_; }

    // Accessors for the left and right sub-trees.
    binary_tree<T>* left() noexcept { return left_.get(); }
    const binary_tree<T>* left() const noexcept { return left_.get(); }

    binary_tree<T>* right() noexcept { return right_.get(); }
    const binary_tree<T>* right() const noexcept { return right_.get(); }

    // Iterator support (in-order traversal)
    using iterator = typename std::vector<T>::const_iterator;

    iterator begin() const
    {
        if (cache_.empty()) {
            cache_ = sorted_data();
        }
        return cache_.cbegin();
    }

    iterator end() const
    {
        if (cache_.empty()) {
            cache_ = sorted_data();
        }
        return cache_.cend();
    }

    // Insert a value while preserving BST ordering.
    void insert(const T& value)
    {
        cache_.clear();
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

    // Determine whether the tree contains a given value.
    bool contains(const T& value) const noexcept
    {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // Return the contents of the tree in sorted (ascending) order.
    std::vector<T> sorted_data() const
    {
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

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{nullptr};
    std::unique_ptr<binary_tree<T>> right_{nullptr};
    mutable std::vector<T> cache_{};
};

// Provide free begin/end overloads so that range-based for works with ADL
template <typename T>
auto begin(const binary_tree<T>& tree) {
    return tree.begin();
}

template <typename T>
auto end(const binary_tree<T>& tree) {
    return tree.end();
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
