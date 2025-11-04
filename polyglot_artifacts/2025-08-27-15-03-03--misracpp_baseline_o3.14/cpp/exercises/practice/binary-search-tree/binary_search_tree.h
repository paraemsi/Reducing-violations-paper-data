#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <stack>

namespace binary_search_tree {

/*
 * A minimal binary search tree that stores comparable values (e.g. int).
 *  - insert(value)   : add value to the tree
 *  - data()          : value stored in the current node
 *  - left()/right()  : access to the left / right sub-trees
 *
 * The entire implementation is kept in-header because the class is
 * templated.  This avoids linker issues with templates.
 */
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : value_{value} {}

    // Return the value stored at this node
    const T& data() const { return value_; }

    // Mutable access to sub-trees
    std::unique_ptr<binary_tree<T>>& left()  { return left_;  }
    std::unique_ptr<binary_tree<T>>& right() { return right_; }

    // Const access to sub-trees
    const std::unique_ptr<binary_tree<T>>& left()  const { return left_;  }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    // Insert `value` into the correct position in the tree
    void insert(const T& value)
    {
        if (value <= value_) {
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

    // Convenience helper: search for `value`, return true if found
    bool contains(const T& value) const
    {
        if (value == value_) {
            return true;
        }
        if (value < value_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // Return all elements of the tree in sorted (in-order) order
    std::vector<T> sorted_data() const
    {
        std::vector<T> result;
        if (left_) {
            auto left_vec = left_->sorted_data();
            result.insert(result.end(), left_vec.begin(), left_vec.end());
        }
        result.push_back(value_);
        if (right_) {
            auto right_vec = right_->sorted_data();
            result.insert(result.end(), right_vec.begin(), right_vec.end());
        }
        return result;
    }

    /* ------------------------------------------------------------------
     *  In-order iterator support so the tree can be used in range-for
     * ------------------------------------------------------------------*/
    class iterator {
        using node_ptr = binary_tree*;
    public:
        iterator() = default;
        explicit iterator(node_ptr node) { push_left(node); }

        T& operator*() const { return stack_.back()->value_; }

        iterator& operator++()
        {
            node_ptr node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        bool operator==(const iterator& other) const
        {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.back() == other.stack_.back();
        }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        void push_left(node_ptr node)
        {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        std::vector<node_ptr> stack_{};
    };

    class const_iterator {
        using node_ptr = const binary_tree*;
    public:
        const_iterator() = default;
        explicit const_iterator(node_ptr node) { push_left(node); }

        const T& operator*() const { return stack_.back()->value_; }

        const_iterator& operator++()
        {
            node_ptr node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        bool operator==(const const_iterator& other) const
        {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.back() == other.stack_.back();
        }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }

    private:
        void push_left(node_ptr node)
        {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        std::vector<node_ptr> stack_{};
    };

    // Range-based for helpers
    iterator begin()               { return iterator(this); }
    iterator end()                 { return iterator(); }
    const_iterator begin() const   { return const_iterator(this); }
    const_iterator end()   const   { return const_iterator(); }

private:
    T value_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
