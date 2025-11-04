#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>   /* for std::ptrdiff_t                                    */
#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

/*
 * A generic binary‐search tree that stores values of type T.
 * Empty trees are allowed; the first inserted value becomes the root.
 *
 * The class fulfils the minimal interface required by the unit tests:
 *  - insert(const T&)
 *  - data()             : root node’s value
 *  - left()/right()     : (unique_ptr&) access to children
 *  - range-for support  : in-order traversal via begin()/end()
 */
template <typename T>
class binary_tree
{
public:
    using value_type = T;
    using tree_ptr   = std::unique_ptr<binary_tree<T>>;

    /* Constructors */
    binary_tree() = default;
    explicit binary_tree(const T& value) : data_{value}, has_value_{true} {}

    /* Disable copy to avoid accidental slicing; use std::unique_ptr instead. */
    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept            = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

    /* Public interface expected by the tests                                    */
    void insert(const T& value)
    {
        if (!has_value_) {
            data_       = value;
            has_value_  = true;
            return;
        }

        insert_impl(*this, value);
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if (!has_value_) {
            return false;
        }
        if (value == data_) {         /* (value == data_) is already parenthesised */
            return true;
        }
        if (value < data_) {          /* (value < data_) parenthesised before && / || */
            return (left_ != nullptr) && (left_->contains(value));
        }
        return (right_ != nullptr) && (right_->contains(value));
    }

    /* Accessors used by the unit-tests */
    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    tree_ptr& left() noexcept
    {
        return left_;
    }
    const tree_ptr& left() const noexcept
    {
        return left_;
    }

    tree_ptr& right() noexcept
    {
        return right_;
    }
    const tree_ptr& right() const noexcept
    {
        return right_;
    }

    /* ---------------- In-order iterator support ------------------------------ */
    class const_iterator
    {
        using node_ptr = const binary_tree<T>*;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;

        explicit const_iterator(node_ptr root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.back()->data_;
        }
        pointer operator->() const
        {
            return &(stack_.back()->data_);
        }

        const_iterator& operator++()
        {
            auto current = stack_.back();
            stack_.pop_back();
            push_left(current->right_.get());
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this); /* mandatory int dummy kept */
            ++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs,
                               const const_iterator& rhs)
        {
            if (lhs.stack_.empty() && rhs.stack_.empty()) {
                return true;
            }
            if (lhs.stack_.empty() || rhs.stack_.empty()) {
                return false;
            }
            return lhs.stack_.back() == rhs.stack_.back();
        }

        friend bool operator!=(const const_iterator& lhs,
                               const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<node_ptr> stack_;

        void push_left(node_ptr node)
        {
            while (node != nullptr) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    using iterator = const_iterator;

    [[nodiscard]] const_iterator begin() const
    {
        return const_iterator(this->has_value_ ? this : nullptr);
    }

    [[nodiscard]] const_iterator end() const
    {
        return const_iterator();
    }

private:
    /* Helper used by insert – works on a (non-null) node reference              */
    static void insert_impl(binary_tree<T>& subtree, const T& value)
    {
        if (value <= subtree.data_) {
            if (subtree.left_ == nullptr) {
                subtree.left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                insert_impl(*(subtree.left_), value);
            }
        } else { /* value  > subtree.data_ */
            if (subtree.right_ == nullptr) {
                subtree.right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                insert_impl(*(subtree.right_), value);
            }
        }
    }

    /* Member data                                                               */
    T                 data_       {};
    bool              has_value_  {false};
    tree_ptr          left_       {};
    tree_ptr          right_      {};
};

} // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
