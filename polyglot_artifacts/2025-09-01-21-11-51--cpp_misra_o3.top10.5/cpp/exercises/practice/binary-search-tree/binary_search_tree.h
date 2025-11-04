#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>

#if __cplusplus < 201703L
#define BST_NODISCARD
#else
#define BST_NODISCARD [[nodiscard]]
#endif

namespace binary_search_tree {

template <typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_{value}
    {
    }

    binary_tree(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&) noexcept = delete;
    ~binary_tree() = default;

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

    BST_NODISCARD bool contains(const T& value) const
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

    BST_NODISCARD const T& data() const noexcept
    {
        return value_;
    }

    std::unique_ptr<binary_tree>& left() noexcept
    {
        return left_;
    }

    const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return left_;
    }

    std::unique_ptr<binary_tree>& right() noexcept
    {
        return right_;
    }

    const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return right_;
    }

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = const T;
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
            return stack_.top()->value_;
        }

        pointer operator->() const
        {
            return &(stack_.top()->value_);
        }

        iterator& operator++()
        {
            const binary_tree* const node = stack_.top();
            stack_.pop();
            if (node->right_ != nullptr)
            {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            (void)++(*this);
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            const bool lhs_empty = lhs.stack_.empty();
            const bool rhs_empty = rhs.stack_.empty();
            if ((lhs_empty) || (rhs_empty))
            {
                return lhs_empty == rhs_empty;
            }
            return lhs.stack_.top() == rhs.stack_.top();
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::stack<const binary_tree*> stack_{};

        void push_left(const binary_tree* node)
        {
            const binary_tree* current = node;
            while (current != nullptr)
            {
                stack_.push(current);
                current = current->left_.get();
            }
        }
    };

    iterator begin() const
    {
        return iterator(this);
    }

    iterator end() const
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
