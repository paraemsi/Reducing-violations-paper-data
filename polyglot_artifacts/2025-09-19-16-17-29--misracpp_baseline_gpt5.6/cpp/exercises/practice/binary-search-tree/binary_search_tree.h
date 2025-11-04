#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iterator>
#include <memory>
#include <stack>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using node_type = binary_tree;
    using value_type = T;
    explicit binary_tree(const T& value) : m_data(value) {}

    // Accessors
    const T& data() const { return m_data; }

    const std::unique_ptr<node_type>& left() const { return m_left; }
    const std::unique_ptr<node_type>& right() const { return m_right; }

    // Insert a value into the tree. Duplicates go to the left subtree.
    void insert(const T& value) {
        if (value <= m_data) {
            if (m_left) {
                m_left->insert(value);
            } else {
                m_left.reset(new node_type(value));
            }
        } else {
            if (m_right) {
                m_right->insert(value);
            } else {
                m_right.reset(new node_type(value));
            }
        }
    }

    // In-order iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        explicit iterator(const node_type* root) { push_left(root); }

        reference operator*() const { return m_stack.top()->m_data; }
        pointer operator->() const { return &m_stack.top()->m_data; }

        iterator& operator++() {
            const node_type* node = m_stack.top();
            m_stack.pop();
            if (node->m_right) {
                push_left(node->m_right.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& a, const iterator& b) {
            if (a.m_stack.empty() && b.m_stack.empty()) return true;
            if (a.m_stack.empty() || b.m_stack.empty()) return false;
            return a.m_stack.top() == b.m_stack.top();
        }
        friend bool operator!=(const iterator& a, const iterator& b) { return !(a == b); }

    private:
        void push_left(const node_type* node) {
            while (node) {
                m_stack.push(node);
                node = node->m_left.get();
            }
        }

        std::stack<const node_type*> m_stack;
    };

    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

    iterator cbegin() const { return iterator(this); }
    iterator cend() const { return iterator(); }

private:
    T m_data;
    std::unique_ptr<node_type> m_left;
    std::unique_ptr<node_type> m_right;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
