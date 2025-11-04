#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

// Generic binary-search tree that stores comparable values.
template <typename T>
class binary_tree {
public:
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value) : m_data{value} {}

    // Value stored in this node
    const T& data() const { return m_data; }

    // Accessors for the left / right sub-trees
    const node_ptr& left() const { return m_left; }
    const node_ptr& right() const { return m_right; }

    // Insert a new value, preserving BST ordering
    void insert(const T& value) {
        if (value <= m_data) {
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

    // Return all elements in sorted (in-order) order
    std::vector<T> sorted_data() const {
        std::vector<T> result;
        if (m_left) {
            auto left_vec = m_left->sorted_data();
            result.insert(result.end(), left_vec.begin(), left_vec.end());
        }
        result.push_back(m_data);
        if (m_right) {
            auto right_vec = m_right->sorted_data();
            result.insert(result.end(), right_vec.begin(), right_vec.end());
        }
        return result;
    }

private:
    T        m_data;
    node_ptr m_left{};
    node_ptr m_right{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
