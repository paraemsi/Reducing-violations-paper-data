#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <iterator>
#include <vector>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    BinarySearchTree() noexcept;
    explicit BinarySearchTree(std::int32_t data) noexcept;

    void insert(std::int32_t value);

    [[nodiscard]] bool search(std::int32_t value) const noexcept;

private:
    bool m_is_initialized;
    std::int32_t m_data;
    std::unique_ptr<BinarySearchTree> m_left;
    std::unique_ptr<BinarySearchTree> m_right;

    void insert_internal(std::unique_ptr<BinarySearchTree>& subtree,
                         std::int32_t value);

    [[nodiscard]] bool search_internal(const BinarySearchTree* subtree,
                                       std::int32_t value) const noexcept;
};

/*
 * Template binary search tree node that the unit-tests expect.
 * Provides data accessors, insertion, and an in-order forward
 * iterator so that the tree can be range-iterated.
 */
template<typename T>
class binary_tree
{
public:
    explicit binary_tree(const T &value) :
        m_data(value),
        m_left(nullptr),
        m_right(nullptr)
    {
    }

    void insert(const T &value)
    {
        if (value <= m_data)
        {
            insert_internal(m_left, value);
        }
        else
        {
            insert_internal(m_right, value);
        }
    }

    [[nodiscard]] const T &data() const noexcept
    {
        return m_data;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree> &left() const noexcept
    {
        return m_left;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree> &right() const noexcept
    {
        return m_right;
    }

    /*
     * In-order forward iterator implementation
     */
    class iterator
    {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = const T &;
        using pointer = const T *;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        reference operator*() const noexcept
        {
            return m_path.back()->m_data;
        }

        pointer operator->() const noexcept
        {
            return &(m_path.back()->m_data);
        }

        iterator &operator++()
        {
            const binary_tree *node = m_path.back();
            m_path.pop_back();

            if (node->m_right != nullptr)
            {
                push_left(node->m_right.get());
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator old(*this);
            static_cast<void>(++(*this));   // required dummy int
            return old;
        }

        [[nodiscard]] bool operator==(const iterator &other) const noexcept
        {
            if (m_path.empty() && other.m_path.empty())
            {
                return true;
            }

            if ((!m_path.empty()) && (!other.m_path.empty()))
            {
                return (m_path.back() == other.m_path.back());
            }

            return false;
        }

        [[nodiscard]] bool operator!=(const iterator &other) const noexcept
        {
            return !((*this) == other);
        }

    private:
        std::vector<const binary_tree *> m_path{};

        explicit iterator(const binary_tree *root)
        {
            push_left(root);
        }

        void push_left(const binary_tree *node)
        {
            const binary_tree *current = node;
            while (current != nullptr)
            {
                m_path.push_back(current);
                current = current->m_left.get();
            }
        }

        friend class binary_tree;
    };

    [[nodiscard]] iterator begin() const noexcept
    {
        return iterator(this);
    }

    [[nodiscard]] static iterator end() noexcept
    {
        return iterator();
    }

private:
    T m_data;
    std::unique_ptr<binary_tree> m_left;
    std::unique_ptr<binary_tree> m_right;

    void insert_internal(std::unique_ptr<binary_tree> &subtree,
                         const T &value)
    {
        if (subtree == nullptr)
        {
            subtree = std::make_unique<binary_tree>(value);
        }
        else
        {
            subtree->insert(value);
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
