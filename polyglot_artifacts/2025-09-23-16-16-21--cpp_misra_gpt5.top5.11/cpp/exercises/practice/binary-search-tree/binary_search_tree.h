#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(T const & value)
        : m_data(value), m_left(nullptr), m_right(nullptr) {}

    void insert(T const & value)
    {
        if ((value <= m_data)) {
            if ((m_left != nullptr)) {
                m_left->insert(value);
            } else {
                m_left = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if ((m_right != nullptr)) {
                m_right->insert(value);
            } else {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    T const & data() const noexcept
    {
        return m_data;
    }

    std::unique_ptr<binary_tree<T>> const & left() const noexcept
    {
        return m_left;
    }

    std::unique_ptr<binary_tree<T>> const & right() const noexcept
    {
        return m_right;
    }

    class iterator {
    public:
        iterator() noexcept = default;

        explicit iterator(binary_tree<T>* root) noexcept
        {
            push_left(root);
        }

        T& operator*() const noexcept
        {
            return (m_path.back()->m_data);
        }

        T* operator->() const noexcept
        {
            return &(m_path.back()->m_data);
        }

        iterator& operator++() noexcept
        {
            binary_tree<T>* node = m_path.back();
            m_path.pop_back();
            if ((node->m_right != nullptr)) {
                push_left(node->m_right.get());
            } else {
                // no-op
            }
            return (*this);
        }

        iterator operator++(int) noexcept
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(iterator const& other) const noexcept
        {
            if ((m_path.empty()) && (other.m_path.empty())) {
                return true;
            } else {
                if ((!m_path.empty()) && (!other.m_path.empty())) {
                    return (m_path.back() == other.m_path.back());
                } else {
                    return false;
                }
            }
        }

        bool operator!=(iterator const& other) const noexcept
        {
            return (!(*this == other));
        }

    private:
        void push_left(binary_tree<T>* node) noexcept
        {
            while ((node != nullptr)) {
                m_path.push_back(node);
                node = node->m_left.get();
            }
        }

        std::vector<binary_tree<T>*> m_path{};
    };

    class const_iterator {
    public:
        const_iterator() noexcept = default;

        explicit const_iterator(binary_tree<T> const* root) noexcept
        {
            push_left(root);
        }

        T const& operator*() const noexcept
        {
            return (m_path.back()->m_data);
        }

        T const* operator->() const noexcept
        {
            return &(m_path.back()->m_data);
        }

        const_iterator& operator++() noexcept
        {
            binary_tree<T> const* node = m_path.back();
            m_path.pop_back();
            if ((node->m_right != nullptr)) {
                push_left(node->m_right.get());
            } else {
                // no-op
            }
            return (*this);
        }

        const_iterator operator++(int) noexcept
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const_iterator const& other) const noexcept
        {
            if ((m_path.empty()) && (other.m_path.empty())) {
                return true;
            } else {
                if ((!m_path.empty()) && (!other.m_path.empty())) {
                    return (m_path.back() == other.m_path.back());
                } else {
                    return false;
                }
            }
        }

        bool operator!=(const_iterator const& other) const noexcept
        {
            return (!(*this == other));
        }

    private:
        void push_left(binary_tree<T> const* node) noexcept
        {
            while ((node != nullptr)) {
                m_path.push_back(node);
                node = node->m_left.get();
            }
        }

        std::vector<binary_tree<T> const*> m_path{};
    };

    iterator begin() noexcept
    {
        return iterator(this);
    }

    iterator end() noexcept
    {
        return iterator(nullptr);
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(this);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(this);
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(nullptr);
    }

    std::vector<T> as_vector() const
    {
        std::vector<T> result{};
        inorder_node(*this, result);
        return result;
    }

    bool contains(T const & value) const noexcept
    {
        if ((value == m_data)) {
            return true;
        } else {
            if ((value <= m_data)) {
                if ((m_left != nullptr)) {
                    return m_left->contains(value);
                } else {
                    return false;
                }
            } else {
                if ((m_right != nullptr)) {
                    return m_right->contains(value);
                } else {
                    return false;
                }
            }
        }
    }

private:
    static void inorder_node(binary_tree<T> const & node, std::vector<T> & out)
    {
        if ((node.m_left != nullptr)) {
            inorder_node(*(node.m_left), out);
        } else {
            // no-op
        }

        out.push_back(node.m_data);

        if ((node.m_right != nullptr)) {
            inorder_node(*(node.m_right), out);
        } else {
            // no-op
        }
    }

    T m_data;
    std::unique_ptr<binary_tree<T>> m_left;
    std::unique_ptr<binary_tree<T>> m_right;
};

template <typename T>
void inorder_collect(binary_tree<T> const & node, std::vector<T> & out)
{
    if ((node.left() != nullptr)) {
        inorder_collect(*(node.left()), out);
    } else {
        // no-op
    }

    out.push_back(node.data());

    if ((node.right() != nullptr)) {
        inorder_collect(*(node.right()), out);
    } else {
        // no-op
    }
}

template <typename T>
std::vector<T> as_vector(binary_tree<T> const & tree)
{
    std::vector<T> result{};
    inorder_collect(tree, result);
    return result;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
