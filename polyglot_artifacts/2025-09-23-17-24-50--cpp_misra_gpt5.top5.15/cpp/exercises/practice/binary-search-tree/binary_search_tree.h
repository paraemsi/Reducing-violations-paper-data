#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : m_data(value), m_left(nullptr), m_right(nullptr) { }

    void insert(const T& value) {
        binary_tree<T>* current = this;

        for (;;) {
            if ((value <= current->m_data)) {
                if (current->m_left) {
                    current = current->m_left.get();
                } else {
                    current->m_left = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
                    break;
                }
            } else {
                if (current->m_right) {
                    current = current->m_right.get();
                } else {
                    current->m_right = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
                    break;
                }
            }
        }
    }

    bool contains(const T& value) const noexcept {
        const binary_tree<T>* current = this;

        while ((current != nullptr)) {
            if ((value == current->m_data)) {
                return true;
            }

            if ((value <= current->m_data)) {
                current = current->m_left.get();
            } else {
                current = current->m_right.get();
            }
        }

        return false;
    }

    const T& data() const noexcept {
        return m_data;
    }

    const binary_tree<T>* left() const noexcept {
        return m_left.get();
    }

    const binary_tree<T>* right() const noexcept {
        return m_right.get();
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = const T&;
        using pointer = const T*;

        iterator() noexcept : m_current(nullptr), m_stack() { }

        explicit iterator(const binary_tree<T>* root) : m_current(nullptr), m_stack() {
            push_left(root);
            set_current_from_stack();
        }

        reference operator*() const {
            return m_current->data();
        }

        pointer operator->() const {
            return &(m_current->data());
        }

        iterator& operator++() {
            if (!(m_stack.empty())) {
                const binary_tree<T>* node = m_stack.back();
                m_stack.pop_back();
                push_left(node->right());
            }
            set_current_from_stack();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            (void) ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const noexcept {
            return (m_current == other.m_current);
        }

        bool operator!=(const iterator& other) const noexcept {
            return (m_current != other.m_current);
        }

    private:
        const binary_tree<T>* m_current;
        std::vector<const binary_tree<T>*> m_stack;

        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* cur = node;
            while ((cur != nullptr)) {
                m_stack.push_back(cur);
                cur = cur->left();
            }
        }

        void set_current_from_stack() {
            if (m_stack.empty()) {
                m_current = nullptr;
            } else {
                m_current = m_stack.back();
            }
        }
    };

    iterator begin() {
        return iterator(this);
    }

    iterator end() {
        return iterator();
    }

    iterator begin() const {
        return iterator(this);
    }

    iterator end() const {
        return iterator();
    }

private:
    T m_data;
    std::unique_ptr<binary_tree<T>> m_left;
    std::unique_ptr<binary_tree<T>> m_right;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
