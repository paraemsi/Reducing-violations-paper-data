#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>

namespace binary_search_tree {

struct Node final
{
    std::int32_t data;
    Node*        left;
    Node*        right;

    explicit Node(std::int32_t value) noexcept : data(value), left(nullptr), right(nullptr) {}
    Node(const Node&)            = delete;
    Node& operator=(const Node&) = delete;
};

class BinarySearchTree final
{
public:
    BinarySearchTree() noexcept : root(nullptr) {}
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const noexcept;

    BinarySearchTree(const BinarySearchTree&)            = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

private:
    Node* root;

    static void insert_impl(Node*& node, std::int32_t value);
    static bool contains_impl(const Node* node, std::int32_t value) noexcept;
    static void clear(Node* node) noexcept;
};

template<typename T>
class binary_tree final
{
public:
    explicit binary_tree(const T& value) :
        m_data(value),
        m_left(nullptr),
        m_right(nullptr),
        m_cache_valid(false)
    {
    }

    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    void insert(const T& value)
    {
        if (value <= m_data)
        {
            if (m_left)
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
            if (m_right)
            {
                m_right->insert(value);
            }
            else
            {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
        }
        invalidate_cache();
    }

    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        if (value == m_data)
        {
            return true;
        }

        if (value < m_data)
        {
            return (m_left != nullptr) && (m_left->contains(value));
        }

        return (m_right != nullptr) && (m_right->contains(value));
    }

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

    using container_type  = std::vector<T>;
    using const_iterator  = typename container_type::const_iterator;

    [[nodiscard]] const_iterator begin() const
    {
        build_cache();
        return m_ordered_cache.cbegin();
    }

    [[nodiscard]] const_iterator end() const
    {
        build_cache();
        return m_ordered_cache.cend();
    }

private:
    T                                    m_data;
    std::unique_ptr<binary_tree<T>>      m_left;
    std::unique_ptr<binary_tree<T>>      m_right;

    mutable container_type               m_ordered_cache;
    mutable bool                         m_cache_valid;

    void invalidate_cache() const noexcept
    {
        m_cache_valid = false;
    }

    void build_cache() const
    {
        if (m_cache_valid)
        {
            return;
        }

        m_ordered_cache.clear();
        in_order_traverse(m_ordered_cache);
        m_cache_valid = true;
    }

    void in_order_traverse(container_type& output) const
    {
        if (m_left)
        {
            m_left->in_order_traverse(output);
        }

        output.push_back(m_data);

        if (m_right)
        {
            m_right->in_order_traverse(output);
        }
    }
};
 
}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
