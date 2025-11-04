#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() noexcept = default;

        explicit iterator(const binary_tree* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.back()->data();
        }

        pointer operator->() const
        {
            return &(stack_.back()->data());
        }

        iterator& operator++()
        {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            const binary_tree* r = node->right().get();
            if ((r != nullptr)) {
                push_left(r);
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const noexcept
        {
            if ((stack_.empty()) && (other.stack_.empty())) {
                return true;
            }
            if ((stack_.empty()) || (other.stack_.empty())) {
                return false;
            }
            return (stack_.back() == other.stack_.back());
        }

        bool operator!=(const iterator& other) const noexcept
        {
            return (!(*this == other));
        }

    private:
        void push_left(const binary_tree* node)
        {
            const binary_tree* cur = node;
            while ((cur != nullptr)) {
                stack_.push_back(cur);
                cur = cur->left().get();
            }
        }

        std::vector<const binary_tree*> stack_{};
    };

    explicit binary_tree(const value_type& value) : data_{value} {}

    void insert(const value_type& value)
    {
        if ((value <= data_)) {
            if (!left_) {
                left_.reset(new binary_tree<value_type>(value));
            } else {
                left_->insert(value);
            }
        } else {
            if (!right_) {
                right_.reset(new binary_tree<value_type>(value));
            } else {
                right_->insert(value);
            }
        }
    }

    const value_type& data() const noexcept
    {
        return data_;
    }


    const std::unique_ptr<binary_tree<value_type>>& left() const noexcept
    {
        return left_;
    }


    const std::unique_ptr<binary_tree<value_type>>& right() const noexcept
    {
        return right_;
    }

    iterator begin() noexcept
    {
        return iterator(this);
    }

    iterator end() noexcept
    {
        return iterator();
    }

    iterator begin() const noexcept
    {
        return iterator(this);
    }

    iterator end() const noexcept
    {
        return iterator();
    }

    bool contains(const value_type& value) const noexcept
    {
        if ((value == data_)) {
            return true;
        } else if ((value < data_)) {
            if (left_) {
                return left_->contains(value);
            } else {
                return false;
            }
        } else {
            if (right_) {
                return right_->contains(value);
            } else {
                return false;
            }
        }
    }

private:
    value_type data_;
    std::unique_ptr<binary_tree<value_type>> left_;
    std::unique_ptr<binary_tree<value_type>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
