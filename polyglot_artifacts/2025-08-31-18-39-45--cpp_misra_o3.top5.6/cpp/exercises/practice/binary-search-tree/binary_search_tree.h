#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <cstddef>
#include <stack>
#include <iterator>
#include <vector>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t value_in) noexcept : value(value_in) { }
        std::int32_t value;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    void insertNode(std::unique_ptr<Node>& root, std::int32_t value);
    [[nodiscard]] bool containsNode(const std::unique_ptr<Node>& root, std::int32_t value) const;

    std::unique_ptr<Node> m_root{nullptr};
};

/*
 * Generic binary search tree used by the unit-tests.
 * All functionality is header-only because the class is templated.
 */
template <typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value_in) : m_value(value_in) { }

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value_in)
    {
        insert_impl(*this, value_in);
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return m_value;
    }

    std::unique_ptr<binary_tree<T>>& left() noexcept
    {
        return m_left;
    }
    const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return m_left;
    }

    std::unique_ptr<binary_tree<T>>& right() noexcept
    {
        return m_right;
    }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return m_right;
    }

    [[nodiscard]] bool contains(const T& value_in) const
    {
        if (value_in == m_value) {
            return true;
        }

        if (value_in <= m_value) {
            return (m_left == nullptr) ? false : m_left->contains(value_in);
        }

        return (m_right == nullptr) ? false : m_right->contains(value_in);
    }

    /* --------------------------------------------------------------------- */
    /*                         in-order iterator                             */
    /* --------------------------------------------------------------------- */
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = const T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return m_stack.top()->m_value;
        }

        pointer operator->() const
        {
            return &(m_stack.top()->m_value);
        }

        iterator& operator++()
        {
            const binary_tree<T>* node = m_stack.top();
            m_stack.pop();
            push_left(node->m_right.get());
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            static_cast<void>(operator++());
            return temp;
        }

        [[nodiscard]] bool operator==(const iterator& other) const noexcept
        {
            if (m_stack.empty() && other.m_stack.empty()) {
                return true;
            }
            if (m_stack.empty() || other.m_stack.empty()) {
                return false;
            }
            return m_stack.top() == other.m_stack.top();
        }

        [[nodiscard]] bool operator!=(const iterator& other) const noexcept
        {
            return !(operator==(other));
        }

    private:
        std::stack<const binary_tree<T>*> m_stack;

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while (current != nullptr) {
                m_stack.push(current);
                current = current->m_left.get();
            }
        }
    };

    iterator begin() const
    {
        return iterator(this);
    }

    iterator end() const
    {
        return iterator();
    }

private:
    static void insert_impl(binary_tree<T>& subtree, const T& value_in)
    {
        if (value_in <= subtree.m_value) {
            if (subtree.m_left == nullptr) {
                subtree.m_left = std::make_unique<binary_tree<T>>(value_in);
            } else {
                insert_impl(*subtree.m_left, value_in);
            }
        } else {
            if (subtree.m_right == nullptr) {
                subtree.m_right = std::make_unique<binary_tree<T>>(value_in);
            } else {
                insert_impl(*subtree.m_right, value_in);
            }
        }
    }

    T m_value;
    std::unique_ptr<binary_tree<T>> m_left{nullptr};
    std::unique_ptr<binary_tree<T>> m_right{nullptr};
};

}  // namespace binary_search_tree

/* -------------------------------------------------------------------------
 * Helper factory required by the unit-tests
 * ------------------------------------------------------------------------- */
template <typename T>
std::unique_ptr<binary_search_tree::binary_tree<T>>
make_tree(const std::vector<T>& data)
{
    if (data.empty()) {
        return nullptr;
    }

    auto root = std::make_unique<binary_search_tree::binary_tree<T>>(data[0U]);
    for (std::size_t idx = 1U; idx < data.size(); ++idx) {
        root->insert(data[idx]);
    }
    return root;
}

#endif // BINARY_SEARCH_TREE_H
