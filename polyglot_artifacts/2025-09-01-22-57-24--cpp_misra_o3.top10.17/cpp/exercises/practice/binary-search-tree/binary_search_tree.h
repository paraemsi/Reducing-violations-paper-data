#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>
#include <cstddef>
#include <iterator>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    explicit BinarySearchTree(std::int32_t value);

    /* Deleted copy operations – std::unique_ptr is non-copyable             */
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    /* Defaulted move operations                                             */
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;

    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        std::int32_t value {};
        std::unique_ptr<Node> left {};
        std::unique_ptr<Node> right {};

        explicit Node(std::int32_t v) : value(v) {}
    };

    std::unique_ptr<Node> root {};

    static void insert_impl(std::unique_ptr<Node>& node, std::int32_t value);
    static bool contains_impl(const std::unique_ptr<Node>& node, std::int32_t value);
};

/* -------------------------------------------------------------------------- */
/*                       Generic binary search tree type                      */
/* -------------------------------------------------------------------------- */

template<typename T>
class binary_tree
{
public:
    /* ---------------------------------------------------------------------- */
    /*                               iterators                                */
    /* ---------------------------------------------------------------------- */
    class const_iterator
    {
    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() = default;

        const_iterator(const std::vector<const T*>* vec, std::size_t idx) noexcept
            : m_vec(vec), m_index(idx)
        {
        }

        reference operator*() const
        {
            return *(m_vec->at(m_index));
        }

        const_iterator& operator++()
        {
            ++m_index;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
        {
            return ((lhs.m_vec == rhs.m_vec) && (lhs.m_index == rhs.m_index));
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        const std::vector<const T*>* m_vec {nullptr};
        std::size_t                  m_index {0U};
    };

    /* ---------------------------------------------------------------------- */
    /*                              constructors                              */
    /* ---------------------------------------------------------------------- */
    explicit binary_tree(const T& value) : m_value(value) {}

    binary_tree() = delete;
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

    /* ---------------------------------------------------------------------- */
    /*                                accessors                               */
    /* ---------------------------------------------------------------------- */
    [[nodiscard]] const T& data() const noexcept
    {
        return m_value;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return m_right;
    }

    /* ---------------------------------------------------------------------- */
    /*                           modifying operations                         */
    /* ---------------------------------------------------------------------- */
    void insert(const T& value)
    {
        if ((value <= m_value))
        {
            if (m_left)
            {
                m_left->insert(value);
            }
            else
            {
                m_left = std::make_unique<binary_tree>(value);
            }
        }
        else
        {
            if (m_right)
            {
                m_right->insert(value);
            }
            else
            {
                m_right = std::make_unique<binary_tree>(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if (value == m_value)
        {
            return true;
        }

        if (value < m_value)
        {
            return (m_left ? m_left->contains(value) : false);
        }

        return (m_right ? m_right->contains(value) : false);
    }

    /* ---------------------------------------------------------------------- */
    /*                                iterators                               */
    /* ---------------------------------------------------------------------- */
    [[nodiscard]] const_iterator begin() const
    {
        m_cache.clear();
        in_order_traverse(this, m_cache);
        return const_iterator(&m_cache, static_cast<std::size_t>(0U));
    }

    [[nodiscard]] const_iterator end() const
    {
        return const_iterator(&m_cache, m_cache.size());
    }

private:
    /* ---------------------------------------------------------------------- */
    /*                              helper funcs                              */
    /* ---------------------------------------------------------------------- */
    static void in_order_traverse(const binary_tree* node, std::vector<const T*>& out)
    {
        if (node == nullptr)
        {
            return;
        }

        in_order_traverse(node->m_left.get(), out);
        out.push_back(&(node->m_value));
        in_order_traverse(node->m_right.get(), out);
    }

    /* ---------------------------------------------------------------------- */
    /*                              data members                              */
    /* ---------------------------------------------------------------------- */
    T                                      m_value;
    std::unique_ptr<binary_tree>           m_left {};
    std::unique_ptr<binary_tree>           m_right {};

    /*  mutable because iterators are logically const                          */
    mutable std::vector<const T*>          m_cache {};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
