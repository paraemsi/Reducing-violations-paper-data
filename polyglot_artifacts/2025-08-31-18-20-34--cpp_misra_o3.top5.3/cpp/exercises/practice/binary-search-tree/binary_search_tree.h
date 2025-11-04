#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <utility>
#include <iterator>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree
{
public:
    explicit binary_tree(const T& data_in)
        : m_data(data_in), m_left(nullptr), m_right(nullptr)
    {
    }

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    [[nodiscard]] const T& data() const noexcept
    {
        return m_data;
    }

    [[nodiscard]] std::unique_ptr<binary_tree<T>>& left() noexcept
    {
        return m_left;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] std::unique_ptr<binary_tree<T>>& right() noexcept
    {
        return m_right;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return m_right;
    }

    void insert(const T& value)
    {
        if ((value <= m_data))
        {
            if (m_left != nullptr)
            {
                m_left->insert(value);
            }
            else
            {
                m_left = std::make_unique<binary_tree<T>>(value);
            }
        }
        else
        {
            if (m_right != nullptr)
            {
                m_right->insert(value);
            }
            else
            {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    // ---------------------------------------------------------------------
    // iterator support – in-order traversal yielding elements in ascending
    // order so the tree can be used in range-based for loops.
    // ---------------------------------------------------------------------
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() noexcept = default;

        explicit iterator(binary_tree<T>* node) noexcept
        {
            push_left(node);
        }

        reference operator*() const noexcept
        {
            return m_stack.back()->m_data;
        }

        pointer operator->() const noexcept
        {
            return &(m_stack.back()->m_data);
        }

        iterator& operator++() noexcept
        {
            auto* node = m_stack.back();
            m_stack.pop_back();
            push_left(node->m_right.get());
            return *this;
        }

        iterator operator++(int) noexcept
        {
            iterator temp(*this);
            static_cast<void>(++(*this));   // mandatory dummy int for postfix
            return temp;
        }

        friend bool operator==(const iterator& lhs,
                               const iterator& rhs) noexcept
        {
            return lhs.current() == rhs.current();
        }

        friend bool operator!=(const iterator& lhs,
                               const iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<binary_tree<T>*> m_stack;

        void push_left(binary_tree<T>* node) noexcept
        {
            while (node != nullptr)
            {
                m_stack.push_back(node);
                node = node->m_left.get();
            }
        }

        binary_tree<T>* current() const noexcept
        {
            return m_stack.empty() ? nullptr : m_stack.back();
        }
    };

    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() noexcept = default;

        explicit const_iterator(const binary_tree<T>* node) noexcept
        {
            push_left(node);
        }

        reference operator*() const noexcept
        {
            return m_stack.back()->m_data;
        }

        pointer operator->() const noexcept
        {
            return &(m_stack.back()->m_data);
        }

        const_iterator& operator++() noexcept
        {
            auto* node = m_stack.back();
            m_stack.pop_back();
            push_left(node->m_right.get());
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            const_iterator temp(*this);
            static_cast<void>(++(*this));   // mandatory dummy int for postfix
            return temp;
        }

        friend bool operator==(const const_iterator& lhs,
                               const const_iterator& rhs) noexcept
        {
            return lhs.current() == rhs.current();
        }

        friend bool operator!=(const const_iterator& lhs,
                               const const_iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree<T>*> m_stack;

        void push_left(const binary_tree<T>* node) noexcept
        {
            while (node != nullptr)
            {
                m_stack.push_back(node);
                node = node->m_left.get();
            }
        }

        const binary_tree<T>* current() const noexcept
        {
            return m_stack.empty() ? nullptr : m_stack.back();
        }
    };

    // begin / end for non-const trees
    [[nodiscard]] iterator begin() noexcept
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end() noexcept
    {
        return iterator();
    }

    // begin / end for const trees
    [[nodiscard]] const_iterator begin() const noexcept
    {
        return const_iterator(this);
    }

    [[nodiscard]] const_iterator end() const noexcept
    {
        return const_iterator();
    }

    // convenience const-range helpers
    [[nodiscard]] const_iterator cbegin() const noexcept
    {
        return begin();
    }

    [[nodiscard]] const_iterator cend() const noexcept
    {
        return end();
    }

private:
    T m_data;
    std::unique_ptr<binary_tree<T>> m_left;
    std::unique_ptr<binary_tree<T>> m_right;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
