#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>

#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard)
#    define BST_NODISCARD [[nodiscard]]
#  else
#    define BST_NODISCARD
#  endif
#else
#  define BST_NODISCARD
#endif

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const value_type& data) : m_data(data) {}

    ~binary_tree() noexcept = default;
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    BST_NODISCARD const value_type& data() const noexcept {
        return m_data;
    }

    BST_NODISCARD const std::unique_ptr<binary_tree<T>>& left() const noexcept {
        return m_left;
    }

    BST_NODISCARD const std::unique_ptr<binary_tree<T>>& right() const noexcept {
        return m_right;
    }

    void insert(const value_type& value) {
        if ((value <= m_data)) {
            if (m_left) {
                m_left->insert(value);
            } else {
                m_left = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (m_right) {
                m_right->insert(value);
            } else {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    BST_NODISCARD bool contains(const value_type& value) const noexcept {
        if ((value == m_data)) {
            return true;
        } else {
            if ((value < m_data)) {
                if (m_left) {
                    return m_left->contains(value);
                } else {
                    return false;
                }
            } else {
                if (m_right) {
                    return m_right->contains(value);
                } else {
                    return false;
                }
            }
        }
    }

private:
    value_type m_data;
    std::unique_ptr<binary_tree<T>> m_left{};
    std::unique_ptr<binary_tree<T>> m_right{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
