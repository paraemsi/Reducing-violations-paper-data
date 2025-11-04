#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

// Forward declaration and helper alias
template <typename T>
class binary_tree;

template <typename T>
using tree_ptr = std::unique_ptr<binary_tree<T>>;

// Generic binary search tree that the unit-tests expect
template <typename T>
class binary_tree
{
public:
    using value_type   = T;
    using pointer_type = tree_ptr<T>;

    explicit binary_tree(const T& data_in) : m_data(data_in) {}

    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept            = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

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

    [[nodiscard]] const T& data() const noexcept
    {
        return m_data;
    }

    pointer_type& left() noexcept
    {
        return m_left;
    }

    pointer_type& right() noexcept
    {
        return m_right;
    }

    [[nodiscard]] const pointer_type& left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] const pointer_type& right() const noexcept
    {
        return m_right;
    }

    // Forward iterator implementing in-order traversal
    class iterator
    {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(binary_tree<T>* root)
        {
            if (root != nullptr)
            {
                push_left(root);
            }
        }

        reference operator*() const
        {
            return m_stack.back()->m_data;
        }

        pointer operator->() const
        {
            return &(m_stack.back()->m_data);
        }

        iterator& operator++()
        {
            binary_tree<T>* node = m_stack.back();
            m_stack.pop_back();
            if (node->m_right != nullptr)
            {
                push_left(node->m_right.get());
            }
            return *this;
        }

        iterator operator++(int) // NOLINTNEXTLINE(readability-identifier-naming)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }

        friend bool operator==(const iterator& a, const iterator& b) noexcept
        {
            return a.m_stack == b.m_stack;
        }

        friend bool operator!=(const iterator& a, const iterator& b) noexcept
        {
            return !(a == b);
        }

    private:
        std::vector<binary_tree<T>*> m_stack;

        void push_left(binary_tree<T>* node)
        {
            while (node != nullptr)
            {
                m_stack.push_back(node);
                node = node->m_left.get();
            }
        }
    };

    iterator begin() noexcept
    {
        return iterator(this);
    }

    iterator end() noexcept
    {
        return iterator();
    }

    [[nodiscard]] iterator begin() const noexcept
    {
        /* const overload to support iteration on const objects */
        return iterator(const_cast<binary_tree<T>*>(this));
    }

    [[nodiscard]] iterator end() const noexcept
    {
        return iterator();
    }

private:
    T           m_data;
    pointer_type m_left{ nullptr };
    pointer_type m_right{ nullptr };
};

class Tree
{
public:
    using value_type = std::int32_t;

    explicit Tree(value_type data);
    Tree(const Tree&) = delete;
    Tree(Tree&&) = delete;
    Tree& operator=(const Tree&) = delete;
    Tree& operator=(Tree&&) = delete;
    ~Tree();

    void insert(value_type data);
    [[nodiscard]] bool contains(value_type data) const;

private:
    struct Node
    {
        value_type data;
        Node* left;
        Node* right;
    };

    Node* m_root;

    static void insert_node(Node*& node, value_type data);
    static bool contains_node(const Node* node, value_type data);
    static void destroy(Node* node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
