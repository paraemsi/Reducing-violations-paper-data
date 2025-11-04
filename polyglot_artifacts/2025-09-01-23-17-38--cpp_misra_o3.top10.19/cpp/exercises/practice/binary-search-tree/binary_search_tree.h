#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

using ValueType = std::int32_t;

/*
 * BinarySearchTree
 * ----------------
 * A simple binary search tree that stores signed 32-bit integers.
 * Provides insertion and lookup (contains) operations.
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

    /* Insert a value into the tree. */
    void insert(ValueType value);

    /* Determine whether the value exists in the tree. */
    [[nodiscard]] bool contains(ValueType value) const noexcept;

private:
    struct Node
    {
        explicit Node(ValueType value_in) : value(value_in), left(nullptr), right(nullptr) {}

        ValueType value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    void insert(std::unique_ptr<Node>& subtree, ValueType value);
    [[nodiscard]] bool contains(const std::unique_ptr<Node>& subtree, ValueType value) const noexcept;

    std::unique_ptr<Node> root{};
};

/* --------------------------------------------------------------------------
 * Generic binary search tree node (binary_tree) template
 * -------------------------------------------------------------------------- */
template<typename T>
class binary_tree
{
public:
    explicit binary_tree(const T& value_in) : value_(value_in), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&) = default;
    ~binary_tree() = default;

    /* Insert a value into the (sub-)tree */
    void insert(const T& value_in)
    {
        if((value_in <= value_))
        {
            if((left_ == nullptr))
            {
                left_ = std::make_unique<binary_tree<T>>(value_in);
            }
            else
            {
                left_->insert(value_in);
            }
        }
        else
        {
            if((right_ == nullptr))
            {
                right_ = std::make_unique<binary_tree<T>>(value_in);
            }
            else
            {
                right_->insert(value_in);
            }
        }
    }

    /* Accessors ----------------------------------------------------------- */
    [[nodiscard]] const T& data() const noexcept
    {
        return value_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

private:
    /* Grant iterator full access to internals */
    friend class iterator;

    T value_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

public:
    /* Iteration support (in-order) --------------------------------------- */
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.back()->value_;
        }

        pointer operator->() const
        {
            return &(stack_.back()->value_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if((node != nullptr) && (node->right_ != nullptr))
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
            if((lhs.stack_.empty()) && (rhs.stack_.empty()))
            {
                return true;
            }
            if((!lhs.stack_.empty()) && (!rhs.stack_.empty()))
            {
                return lhs.stack_.back() == rhs.stack_.back();
            }
            return false;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while(current != nullptr)
            {
                stack_.push_back(current);
                current = (current->left_ != nullptr) ? current->left_.get() : nullptr;
            }
        }
    };

    /* Range-for helpers --------------------------------------------------- */
    [[nodiscard]] iterator begin() const
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end() const
    {
        return iterator();
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
