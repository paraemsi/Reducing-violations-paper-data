#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <iterator>
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value) : m_data(value) {}

    void insert(const T& value)
    {
        if (value <= m_data)
        {
            if (m_left == nullptr)
            {
                m_left = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                m_left->insert(value);
            }
        }
        else
        {
            if (m_right == nullptr)
            {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                m_right->insert(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if (value == m_data)
        {
            return true;
        }

        if (value < m_data)
        {
            if (m_left == nullptr)
            {
                return false;
            }
            return m_left->contains(value);
        }

        /* value > m_data */
        if (m_right == nullptr)
        {
            return false;
        }
        return m_right->contains(value);
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return m_data;
    }

    [[nodiscard]] const binary_tree* left() const noexcept
    {
        return m_left.get();
    }

    [[nodiscard]] const binary_tree* right() const noexcept
    {
        return m_right.get();
    }

    [[nodiscard]] std::vector<T> sorted_data() const
    {
        std::vector<T> result{};

        if (m_left != nullptr)
        {
            auto left_vec{m_left->sorted_data()};
            result.insert(result.end(), left_vec.begin(), left_vec.end());
        }

        result.push_back(m_data);

        if (m_right != nullptr)
        {
            auto right_vec{m_right->sorted_data()};
            result.insert(result.end(), right_vec.begin(), right_vec.end());
        }

        return result;
    }

    /* ---------------------------------------------------------------------- */
    /* iterator for range-based for (in-order traversal)                      */
    /* ---------------------------------------------------------------------- */
    class iterator
    {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree* node) { push_left(node); }

        reference operator*() const { return m_stack.back()->m_data; }
        pointer operator->() const { return &(m_stack.back()->m_data); }

        iterator& operator++()
        {
            const binary_tree* current{m_stack.back()};
            m_stack.pop_back();
            if (current->m_right != nullptr)
            {
                push_left(current->m_right.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp{*this}; // mandatory int dummy
            ++(*this);
            return temp;
        }

        [[nodiscard]] bool operator==(const iterator& other) const noexcept
        {
            if ((m_stack.empty()) && (other.m_stack.empty()))
            {
                return true;
            }
            if ((!m_stack.empty()) && (!other.m_stack.empty()))
            {
                return (m_stack.back() == other.m_stack.back());
            }
            return false;
        }

        [[nodiscard]] bool operator!=(const iterator& other) const noexcept
        {
            return !(*this == other);
        }

    private:
        void push_left(const binary_tree* node)
        {
            const binary_tree* current{node};
            while (current != nullptr)
            {
                m_stack.push_back(current);
                current = current->m_left.get();
            }
        }

        std::vector<const binary_tree*> m_stack{};
    };

    [[nodiscard]] iterator begin() const { return iterator{this}; }
    [[nodiscard]] iterator end() const { return iterator{}; }

private:
    T m_data{};
    std::unique_ptr<binary_tree<T>> m_left{nullptr};
    std::unique_ptr<binary_tree<T>> m_right{nullptr};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
