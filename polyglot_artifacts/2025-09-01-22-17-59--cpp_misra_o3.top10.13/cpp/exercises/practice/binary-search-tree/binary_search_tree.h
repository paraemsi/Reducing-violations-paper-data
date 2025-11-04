#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstdint>
#include <memory>
#include <vector>
#include <cstddef>
#include <iterator>   // std::forward_iterator_tag

namespace binary_search_tree {

// Fixed-width alias for the value stored in the tree
using value_type = std::int32_t;

class BinarySearchTree final
{
private:
    struct Node
    {
        value_type value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(value_type v) noexcept;
        Node(const Node&) = delete;
        Node(Node&&) noexcept = default;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&) noexcept = default;
        ~Node() = default;

        void insert(value_type v);
        [[nodiscard]] bool contains(value_type v) const noexcept;
    };

    std::unique_ptr<Node> root{nullptr};

public:
    BinarySearchTree() noexcept = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    void insert(value_type v);
    [[nodiscard]] bool contains(value_type v) const noexcept;
};

/* --------------------------------------------------------------------------
 * Generic binary_search_tree::binary_tree<T>
 * This is the node type expected by the tests.  It owns its sub-trees via
 * std::unique_ptr, provides left()/right()/data() accessors, an insert()
 * mutator, a contains() query, and a forward iterator that walks the tree
 * in-order.
 * -------------------------------------------------------------------------- */
template <typename T>
class binary_tree final
{
private:
    T m_value;
    std::unique_ptr<binary_tree<T>> m_left;
    std::unique_ptr<binary_tree<T>> m_right;

    /* Helper used by the iterator to push the entire left spine. */
    static void push_left_branch(std::vector<const binary_tree<T> *> &stk,
                                 const binary_tree<T> *node) noexcept
    {
        while (node != nullptr)
        {
            stk.push_back(node);
            node = node->m_left.get();
        }
    }

public:
    explicit binary_tree(const T &value) : m_value(value) {}

    binary_tree(const binary_tree &) = delete;
    binary_tree(binary_tree &&) noexcept = default;
    binary_tree &operator=(const binary_tree &) = delete;
    binary_tree &operator=(binary_tree &&) noexcept = default;
    ~binary_tree() = default;

    /* ------------------------------------------------------------------ */
    /* Accessors                                                          */
    /* ------------------------------------------------------------------ */
    [[nodiscard]] const T &data() const noexcept { return m_value; }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>> &left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>> &right() const noexcept
    {
        return m_right;
    }

    /* ------------------------------------------------------------------ */
    /* Mutators / queries                                                 */
    /* ------------------------------------------------------------------ */
    void insert(const T &value)
    {
        if (value <= m_value)
        {
            if (m_left == nullptr)
            {
                m_left = std::make_unique<binary_tree>(value);
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
                m_right = std::make_unique<binary_tree>(value);
            }
            else
            {
                m_right->insert(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T &value) const noexcept
    {
        if (value == m_value)
        {
            return true;
        }

        if (value < m_value)
        {
            return (m_left == nullptr) ? false : m_left->contains(value);
        }

        /* value > m_value */
        return (m_right == nullptr) ? false : m_right->contains(value);
    }

    /* ------------------------------------------------------------------ */
    /* Forward iterator (in-order traversal)                              */
    /* ------------------------------------------------------------------ */
    class iterator
    {
    private:
        std::vector<const binary_tree<T> *> m_stack;

    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T *;
        using reference         = const T &;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(const binary_tree<T> *root)
        {
            push_left_branch(m_stack, root);
        }

        reference operator*() const { return m_stack.back()->m_value; }
        pointer   operator->() const { return &(m_stack.back()->m_value); }

        iterator &operator++()
        {
            const binary_tree<T> *node = m_stack.back();
            m_stack.pop_back();
            if (node->m_right != nullptr)
            {
                push_left_branch(m_stack, node->m_right.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);   /* mandatory int dummy kept */
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator &lhs,
                               const iterator &rhs) noexcept
        {
            return (lhs.m_stack.empty() && rhs.m_stack.empty()) ||
                   ((!lhs.m_stack.empty()) && (!rhs.m_stack.empty()) &&
                    (lhs.m_stack.back() == rhs.m_stack.back()));
        }

        friend bool operator!=(const iterator &lhs,
                               const iterator &rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };

    [[nodiscard]] iterator begin() const { return iterator(this); }
    [[nodiscard]] iterator end()   const { return iterator(); }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
