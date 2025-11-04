#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>
#include <memory>
#include <stack>
#include <iterator>

namespace binary_search_tree {

/*
 * Node structure used internally by BinarySearchTree.
 * Stores a single 32-bit signed integer and raw pointer children.
 */
struct Node
{
    explicit Node(std::int32_t val) noexcept;

    std::int32_t data;
    Node*          left;
    Node*          right;
};

/* ---------------------------------------------------------------------------
 * Generic binary_tree implementation used by the unit-tests.
 * It is a header-only, templated self-contained binary search tree
 * that stores values of arbitrary comparable type T.
 * --------------------------------------------------------------------------*/
template<typename T>
class binary_tree
{
public:
    /* iterator performing an in-order traversal */
    class iterator
    {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::forward_iterator_tag;

        iterator() noexcept = default;

        explicit iterator(const binary_tree<T>* root, bool at_begin)
        {
            if (at_begin && (root != nullptr))
            {
                push_left(root);
            }
        }

        reference operator*() const noexcept
        {
            return (m_stack.top()->m_data);
        }

        pointer operator->() const noexcept
        {
            return (&(m_stack.top()->m_data));
        }

        iterator& operator++() noexcept
        {
            const binary_tree<T>* node { m_stack.top() };
            m_stack.pop();
            if (node->m_right)
            {
                push_left(node->m_right.get());
            }
            return *this;
        }

        iterator operator++(int) noexcept
        {
            iterator temp { *this };
            static_cast<void>(operator++());
            return temp;
        }

        [[nodiscard]] friend bool operator==(const iterator& lhs,
                                             const iterator& rhs) noexcept
        {
            if (lhs.m_stack.empty() && rhs.m_stack.empty())
            {
                return true;
            }
            if (lhs.m_stack.empty() || rhs.m_stack.empty())
            {
                return false;
            }
            return (lhs.m_stack.top() == rhs.m_stack.top());
        }

        [[nodiscard]] friend bool operator!=(const iterator& lhs,
                                             const iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        void push_left(const binary_tree<T>* node) noexcept
        {
            const binary_tree<T>* current { node };
            while (current != nullptr)
            {
                m_stack.push(current);
                current = current->m_left.get();
            }
        }

        std::stack<const binary_tree<T>*> m_stack {};
    };

    /* construct an empty tree */
    binary_tree() noexcept = default;

    /* construct a leaf with the given value */
    explicit binary_tree(const T& value)
        : m_data(value),
          m_has_value(true)
    {
        /* empty */
    }

    /* disallow copy to comply with internal raw pointer storage below */
    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    /* allow move semantics */
    binary_tree(binary_tree&&)            = default;
    binary_tree& operator=(binary_tree&&) = default;

    /* insert a new value into the tree */
    void insert(const T& value)
    {
        if (!m_has_value)
        {
            m_data      = value;
            m_has_value = true;
            return;
        }

        if ((value <= m_data))
        {
            if (!m_left)
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
            if (!m_right)
            {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                m_right->insert(value);
            }
        }
    }

    /* accessors used by the tests */
    [[nodiscard]] const T& data() const noexcept
    {
        return m_data;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return m_right;
    }

    /* STL-style iteration (in-order) */
    [[nodiscard]] iterator begin() const noexcept
    {
        return iterator(this, true);
    }

    [[nodiscard]] iterator end() const noexcept
    {
        return iterator();
    }

private:
    T m_data {};
    bool m_has_value { false };
    std::unique_ptr<binary_tree<T>> m_left  {};
    std::unique_ptr<binary_tree<T>> m_right {};
};

/*
 * A simple binary search tree that supports insertion and lookup.
 */
class BinarySearchTree
{
public:
    BinarySearchTree() noexcept  = default;
    BinarySearchTree(const BinarySearchTree& ) = delete;
    BinarySearchTree(BinarySearchTree&& )      = default;
    BinarySearchTree& operator=(const BinarySearchTree& ) = delete;
    BinarySearchTree& operator=(BinarySearchTree&& )      = default;
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    void insertHelper(Node*& current, std::int32_t value);
    [[nodiscard]] bool containsHelper(const Node* current, std::int32_t value) const;
    static void destroy(Node* node) noexcept;

    Node* m_root { nullptr };
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
