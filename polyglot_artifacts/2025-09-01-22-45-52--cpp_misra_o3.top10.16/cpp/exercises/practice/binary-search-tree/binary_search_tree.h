#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value) :
        data_{value},
        left_{nullptr},
        right_{nullptr}
    {
    }

    binary_tree(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&) = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if(value <= data_)
        {
            if(left_ == nullptr)
            {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                left_->insert(value);
            }
        }
        else
        {
            if(right_ == nullptr)
            {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                right_->insert(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if(value == data_)
        {
            return true;
        }
        if(value < data_)
        {
            return (left_ != nullptr) ? left_->contains(value) : false;
        }
        return (right_ != nullptr) ? right_->contains(value) : false;
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const tree_ptr& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const tree_ptr& right() const noexcept
    {
        return right_;
    }

    /* Const forward iterator performing in-order traversal */
    class const_iterator {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() :
            current_{nullptr}
        {
        }

        explicit const_iterator(const binary_tree<T>* root)
        {
            push_left(root);
            current_ = stack_.empty() ? nullptr : stack_.back();
        }

        reference operator*() const
        {
            return current_->data_;
        }

        pointer operator->() const
        {
            return &(current_->data_);
        }

        const_iterator& operator++()
        {
            advance();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator temp(*this);   /* NOLINT(readability-identifier-naming) */
            (void)++(*this);
            return temp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
        {
            return lhs.current_ == rhs.current_;
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* cursor = node;
            while(cursor != nullptr)
            {
                stack_.push_back(cursor);
                cursor = cursor->left_.get();
            }
        }

        void advance()
        {
            if(stack_.empty())
            {
                current_ = nullptr;
                return;
            }

            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            current_ = stack_.empty() ? nullptr : stack_.back();
        }
    };

    const_iterator begin() const
    {
        return const_iterator(this);
    }

    const_iterator end() const
    {
        return const_iterator();
    }

private:
    T          data_;
    tree_ptr   left_;
    tree_ptr   right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
