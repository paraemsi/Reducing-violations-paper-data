#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>     // for std::ptrdiff_t
#include <memory>      // for std::unique_ptr
#include <vector>      // for std::vector used by iterator
#include <iterator>    // for std::forward_iterator_tag

#if (__cplusplus >= 201703L)
#define BST_NODISCARD [[nodiscard]]
#else
#define BST_NODISCARD
#endif

namespace binary_search_tree {

class BinarySearchTree final
{
public:
    BinarySearchTree() noexcept;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value) noexcept;
    BST_NODISCARD bool contains(std::int32_t value) const noexcept;

private:
    struct Node
    {
        explicit Node(std::int32_t val) noexcept
            : data(val),
              left(nullptr),
              right(nullptr)
        {
        }

        std::int32_t data;
        Node* left;
        Node* right;
    };

    Node* m_root;

    static Node* insert_recursive(Node* node, std::int32_t value) noexcept;
    static bool contains_recursive(const Node* node, std::int32_t value) noexcept;
    static void destroy_recursive(Node* node) noexcept;
};

/*
 * Generic binary-tree implementation that satisfies the public
 * interface expected by the unit tests in binary_search_tree_test.cpp.
 *
 * The class template is entirely header-only so that template
 * instantiation works without additional object files.
 */
template<typename T>
class binary_tree final
{
public:
    /* explicit single-value constructor */
    explicit binary_tree(const T& value) :
        m_data(value),
        m_left(nullptr),
        m_right(nullptr)
    {
    }

    /* disallow copying to keep ownership unique */
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    /* allow moving */
    binary_tree(binary_tree&&) noexcept            = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree()                                 = default;

    /* insert ‑ duplicates are stored in the left sub-tree */
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

    /* true if an equivalent value exists in the tree */
    BST_NODISCARD bool contains(const T& value) const noexcept
    {
        if ((value == m_data))
        {
            return true;
        }

        if ((value < m_data))
        {
            return (m_left != nullptr) ? m_left->contains(value) : false;
        }

        return (m_right != nullptr) ? m_right->contains(value) : false;
    }

    /* accessors used by the unit tests */
    BST_NODISCARD const T& data()   const noexcept { return m_data;  }
    BST_NODISCARD const binary_tree* left()  const noexcept { return m_left.get();  }
    BST_NODISCARD const binary_tree* right() const noexcept { return m_right.get(); }

    /*
     * Forward const-iterator performing an in-order traversal.
     * It fulfils the minimum requirements of an STL ForwardIterator.
     */
    class const_iterator
    {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() noexcept :
            m_current(nullptr)
        {
        }

        explicit const_iterator(const binary_tree* root)
        {
            push_left(root);
            advance();
        }

        reference operator*() const noexcept { return m_current->m_data; }
        pointer   operator->() const noexcept { return &(m_current->m_data); }

        /* pre-increment */
        const_iterator& operator++() noexcept
        {
            advance();
            return *this;
        }

        /* post-increment (dummy int mandated by MISRA) */
        const_iterator operator++(int) noexcept
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
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
        const binary_tree*               m_current;
        std::vector<const binary_tree*>  m_stack;

        void push_left(const binary_tree* node)
        {
            const binary_tree* iter = node;
            while (iter != nullptr)
            {
                m_stack.push_back(iter);
                iter = iter->m_left.get();
            }
        }

        void advance()
        {
            if (m_stack.empty())
            {
                m_current = nullptr;
                return;
            }

            m_current = m_stack.back();
            m_stack.pop_back();

            if (m_current->m_right != nullptr)
            {
                push_left(m_current->m_right.get());
            }
        }
    }; /* class const_iterator */

    BST_NODISCARD const_iterator begin() const { return const_iterator(this); }
    BST_NODISCARD const_iterator end()   const noexcept { return const_iterator(); }

private:
    T                                           m_data;
    std::unique_ptr<binary_tree<T>>             m_left;
    std::unique_ptr<binary_tree<T>>             m_right;
};
}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
