#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <cstddef>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree;   /* forward-declaration needed by unit tests           */

class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t v) : data(v) {}

        std::int32_t data;
        std::unique_ptr<Node> left {nullptr};
        std::unique_ptr<Node> right {nullptr};
    };

    void insert(std::unique_ptr<Node>& root, std::int32_t value);
    [[nodiscard]] bool contains(const std::unique_ptr<Node>& root, std::int32_t value) const;
    static std::unique_ptr<Node> clone(const std::unique_ptr<Node>& node);

    std::unique_ptr<Node> m_root {nullptr};
};

/*
 * Stand-alone binary search tree node that matches the public interface
 * expected by the unit tests (template, data()/left()/right(), iterator, etc.).
 * It is independent from the BinarySearchTree wrapper above so existing code
 * that already uses BinarySearchTree continues to work unchanged.
 */
template<typename T>
class binary_tree
{
public:
    /* iterator that yields an in-order sequence of node data                */
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() noexcept = default;

        explicit iterator(const binary_tree* root) noexcept
        {
            push_left(root);
        }

        reference operator*() const noexcept
        {
            return m_stack.top()->m_data;
        }

        pointer operator->() const noexcept
        {
            return &(m_stack.top()->m_data);
        }

        iterator& operator++() noexcept
        {
            const binary_tree* node = m_stack.top();
            m_stack.pop();
            if (node->m_right != nullptr)
            {
                push_left(node->m_right.get());
            }
            return *this;
        }

        iterator operator++(int) noexcept
        {
            iterator temp(*this);   /* mandatory dummy param kept (MISRA)   */
            ++(*this);
            return temp;
        }

        friend bool operator==(const iterator& lhs,
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
            return lhs.m_stack.top() == rhs.m_stack.top();
        }

        friend bool operator!=(const iterator& lhs,
                               const iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        void push_left(const binary_tree* node) noexcept
        {
            const binary_tree* current = node;
            while (current != nullptr)
            {
                m_stack.push(current);
                if (current->m_left != nullptr)
                {
                    current = current->m_left.get();
                }
                else
                {
                    current = nullptr;
                }
            }
        }

        std::stack<const binary_tree*> m_stack {};
    };

    explicit binary_tree(const T& value)
        : m_data(value)
    {
    }

    void insert(const T& value)
    {
        if ((value <= m_data))
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

    [[nodiscard]] const T& data() const noexcept
    {
        return m_data;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return m_right;
    }

    [[nodiscard]] iterator begin() const noexcept
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end() const noexcept
    {
        return iterator();
    }

private:
    T m_data;                                          /* stored payload   */
    std::unique_ptr<binary_tree> m_left  {nullptr};    /* ≤ m_data subtree */
    std::unique_ptr<binary_tree> m_right {nullptr};    /*  > m_data subtree*/
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
