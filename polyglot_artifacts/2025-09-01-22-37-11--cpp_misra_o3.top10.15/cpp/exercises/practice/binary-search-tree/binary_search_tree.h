#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <stack>
#include <initializer_list>

namespace binary_search_tree {

/*
 * Generic binary search tree that supports:
 *   • insertion of duplicate values (duplicates stored in the left subtree)
 *   • lookup via contains()
 *   • left()/right() accessors returning unique_ptr-based sub-trees
 *   • in-order iteration producing the elements in sorted order
 */
template<typename T>
class binary_tree
{
public:
    using value_type = T;
    using tree_ptr   = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value_in) : m_data(value_in), m_left(nullptr), m_right(nullptr) {}

    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept        = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if((value <= m_data))
        {
            if(!m_left)
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
            if(!m_right)
            {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                m_right->insert(value);
            }
        }
    }

    bool contains(const T& value) const
    {
        if(value == m_data)
        {
            return true;
        }

        if((value < m_data))
        {
            return (m_left != nullptr) ? m_left->contains(value) : false;
        }

        return (m_right != nullptr) ? m_right->contains(value) : false;
    }

    const T& data() const noexcept
    {
        return m_data;
    }

    const tree_ptr& left() const noexcept
    {
        return m_left;
    }

    const tree_ptr& right() const noexcept
    {
        return m_right;
    }

    /* ============================================================
     *                    In-order const iterator
     * ============================================================
     */
    class const_iterator
    {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() noexcept : m_current(nullptr) {}

        explicit const_iterator(const binary_tree<T>* node)
        {
            pushLeft(node);
        }

        reference operator*() const noexcept
        {
            return m_current->m_data;
        }

        pointer operator->() const noexcept
        {
            return &(m_current->m_data);
        }

        const_iterator& operator++() noexcept
        {
            advance();
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            const_iterator temp(*this);   /* mandatory dummy parameter preserved */
            advance();
            return temp;
        }

        friend bool operator==(const const_iterator& lhs,
                               const const_iterator& rhs) noexcept
        {
            return lhs.m_current == rhs.m_current;
        }

        friend bool operator!=(const const_iterator& lhs,
                               const const_iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        std::stack<const binary_tree<T>*> m_stack;
        const binary_tree<T>*             m_current;

        void pushLeft(const binary_tree<T>* node)
        {
            const binary_tree<T>* walker = node;
            while(walker != nullptr)
            {
                m_stack.push(walker);
                walker = (walker->m_left != nullptr) ? walker->m_left.get() : nullptr;
            }

            m_current = (!m_stack.empty()) ? m_stack.top() : nullptr;
        }

        void advance()
        {
            if(m_stack.empty())
            {
                m_current = nullptr;
                return;
            }

            const binary_tree<T>* top_node = m_stack.top();
            m_stack.pop();

            if(top_node->m_right != nullptr)
            {
                pushLeft(top_node->m_right.get());
            }
            else
            {
                m_current = (!m_stack.empty()) ? m_stack.top() : nullptr;
            }
        }
    };

    const_iterator begin() noexcept
    {
        return const_iterator(this);
    }


private:
    T         m_data;
    tree_ptr  m_left;
    tree_ptr  m_right;
};

/* ============================================================
 *                  make_tree helper function
 * ============================================================ */
template<typename T>
inline typename binary_tree<T>::tree_ptr
make_tree(const std::initializer_list<T>& values)
{
    if(values.size() == static_cast<std::size_t>(0))
    {
        return nullptr;
    }

    auto iter = values.begin();
    auto root = std::make_unique<binary_tree<T>>(*iter);
    ++iter;

    for(; iter != values.end(); ++iter)
    {
        root->insert(*iter);
    }

    return root;
}

} // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
