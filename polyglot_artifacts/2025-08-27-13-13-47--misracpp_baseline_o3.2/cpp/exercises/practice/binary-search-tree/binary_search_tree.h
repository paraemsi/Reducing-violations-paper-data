#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Construct a tree from a non-empty list of values – the first
    // value becomes the root, the rest are inserted in order.
    explicit binary_tree(const std::vector<T>& values)
        : m_data(values.at(0))
    {
        for (std::size_t i = 1; i < values.size(); ++i) {
            insert(values[i]);
        }
    }

    // Convenience constructor for creating a single-node tree.
    explicit binary_tree(const T& value)
        : m_data(value) {}

    // Insert a value into the tree, preserving the BST ordering rule.
    void insert(const T& value)
    {
        if (value <= m_data) {
            if (m_left) {
                m_left->insert(value);
            } else {
                m_left = std::make_unique<binary_tree<T>>(value);
            }
        } else { // value > m_data
            if (m_right) {
                m_right->insert(value);
            } else {
                m_right = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    // Return the value stored in this node.
    const T& data() const { return m_data; }

    // Return references to the left / right sub-trees (may be nullptr).
    std::unique_ptr<binary_tree<T>>& left() { return m_left; }
    std::unique_ptr<binary_tree<T>>& right() { return m_right; }

    // Const-qualified accessors
    const std::unique_ptr<binary_tree<T>>& left() const { return m_left; }
    const std::unique_ptr<binary_tree<T>>& right() const { return m_right; }

private:
    T m_data;
    std::unique_ptr<binary_tree<T>> m_left{};
    std::unique_ptr<binary_tree<T>> m_right{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
