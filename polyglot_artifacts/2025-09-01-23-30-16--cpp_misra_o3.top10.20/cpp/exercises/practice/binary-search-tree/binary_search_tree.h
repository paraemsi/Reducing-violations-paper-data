#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>   // for std::ptrdiff_t

namespace binary_search_tree {

/*
 * BinarySearchTree
 * A simple binary search tree that stores 32-bit signed integers
 * and supports insertion and membership query.
 */
class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = default;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = default;
    ~BinarySearchTree() = default;

    /* Insert a value into the tree */
    void insert(std::int32_t value);

    /* Check whether a value exists in the tree */
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t v) : data(v) { }
        std::int32_t data;
        std::unique_ptr<Node> left { nullptr };
        std::unique_ptr<Node> right { nullptr };
    };

    void insert(std::unique_ptr<Node>& current, std::int32_t value);
    [[nodiscard]] bool contains(const std::unique_ptr<Node>& current, std::int32_t value) const;

    std::unique_ptr<Node> root_ { nullptr };
};

/*
 * binary_tree
 * A header-only, minimal binary search tree template that matches
 * the public interface expected by the tests (data(), left(), right(),
 * insert(), contains(), begin()/end()).
 */
template <typename T>
class binary_tree
{
public:
    /* Constructors */
    binary_tree() = delete;
    explicit binary_tree(const T& value) : value_(value) { }

    /* Non-copyable, movable */
    binary_tree(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    /* Basic accessors */
    [[nodiscard]] const T& data() const noexcept
    {
        return value_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return right_;
    }

    /* Modifiers */
    void insert(const T& value)
    {
        if (value <= value_)
        {
            if (left_ == nullptr)
            {
                left_ = std::make_unique<binary_tree>(value);
            }
            else
            {
                left_->insert(value);
            }
        }
        else
        {
            if (right_ == nullptr)
            {
                right_ = std::make_unique<binary_tree>(value);
            }
            else
            {
                right_->insert(value);
            }
        }
    }

    /* Queries */
    [[nodiscard]] bool contains(const T& value) const
    {
        if (value == value_)
        {
            return true;
        }
        if (value < value_)
        {
            return (left_ != nullptr) && (left_->contains(value));
        }
        return (right_ != nullptr) && (right_->contains(value));
    }

    /* Forward iterator (in-order traversal) */
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return path_.back()->value_;
        }

        pointer operator->() const
        {
            return &(path_.back()->value_);
        }

        iterator& operator++()
        {
            const binary_tree* node = path_.back();
            path_.pop_back();
            if (node->right_ != nullptr)
            {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            (void)++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            if (lhs.path_.empty() || rhs.path_.empty())
            {
                return lhs.path_.empty() && rhs.path_.empty();
            }
            return lhs.path_.back() == rhs.path_.back();
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree*> path_{};

        void push_left(const binary_tree* node)
        {
            const binary_tree* current = node;
            while (current != nullptr)
            {
                path_.push_back(current);
                current = current->left_.get();
            }
        }
    };

    /* begin/end helpers */
    [[nodiscard]] iterator begin() const
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end() const
    {
        return iterator();
    }

private:
    T value_;
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
