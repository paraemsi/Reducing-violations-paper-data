#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>          // for std::ptrdiff_t
#include <iterator>         // for std::forward_iterator_tag
#include <memory>
#include <vector>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    void insert(std::int32_t value);
    bool contains(std::int32_t value) const;

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;

private:
    struct Node;
    std::unique_ptr<Node> root_{};
};  // class BinarySearchTree

template<typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value_in) :
        data_{value_in},
        left_{nullptr},
        right_{nullptr}
    {
    }

    void insert(const T& value_in)
    {
        if(value_in <= data_)
        {
            if(left_ == nullptr)
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
            if(right_ == nullptr)
            {
                right_ = std::make_unique<binary_tree<T>>(value_in);
            }
            else
            {
                right_->insert(value_in);
            }
        }
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

    /* Iterator providing in-order traversal */
    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;

        explicit const_iterator(const binary_tree<T>* root)
        {
            push_left(root);
            step();
        }

        reference operator*() const noexcept
        {
            return *current_;
        }

        pointer operator->() const noexcept
        {
            return current_;
        }

        const_iterator& operator++()
        {
            step();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            step();
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs,
                               const const_iterator& rhs) noexcept
        {
            return lhs.current_ == rhs.current_;
        }

        friend bool operator!=(const const_iterator& lhs,
                               const const_iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        void push_left(const binary_tree<T>* node)
        {
            auto local = node;
            while(local != nullptr)
            {
                stack_.push_back(local);
                local = local->left_.get();
            }
        }

        void step()
        {
            if(stack_.empty())
            {
                current_ = nullptr;
                return;
            }

            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            current_ = &(node->data_);

            if(node->right_ != nullptr)
            {
                push_left(node->right_.get());
            }
        }

        const T* current_{nullptr};
        std::vector<const binary_tree<T>*> stack_{};
    };  // class const_iterator

    [[nodiscard]] const_iterator begin()
    {
        return const_iterator(this);
    }

    [[nodiscard]] const_iterator end()
    {
        return const_iterator{};
    }

    [[nodiscard]] const_iterator begin() const
    {
        return const_iterator(this);
    }

    [[nodiscard]] const_iterator end() const
    {
        return const_iterator{};
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};  // class binary_tree

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
