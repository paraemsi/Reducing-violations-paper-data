#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
private:
    T data_value;
    binary_tree<T>* left_ptr;
    binary_tree<T>* right_ptr;

public:
    binary_tree(T value) : data_value(value), left_ptr(nullptr), right_ptr(nullptr) {}
    ~binary_tree() {
        delete left_ptr;
        delete right_ptr;
    }

    T data() const { return data_value; }
    binary_tree<T>* left() const { return left_ptr; }
    binary_tree<T>* right() const { return right_ptr; }

    // Iterator for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator(const binary_tree<T>* node) : stack() {
            if (node != nullptr) {
                push_left(node);
            }
        }
        iterator() : stack() {} // end iterator

        reference operator*() const {
            return stack.top()->data();
        }
        pointer operator->() const {
            return &stack.top()->data();
        }
        iterator& operator++() {
            const binary_tree<T>* node = stack.top();
            stack.pop();
            if (node->right() != nullptr) {
                push_left(node->right());
            }
            return *this;
        }
        bool operator==(const iterator& other) const {
            if ((stack.empty()) && (other.stack.empty())) {
                return true;
            }
            if ((stack.empty()) || (other.stack.empty())) {
                return false;
            }
            return ((stack.top()) == (other.stack.top()));
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const binary_tree<T>*> stack;
        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* current = node;
            while (current != nullptr) {
                stack.push(current);
                current = current->left();
            }
        }
    };

    iterator begin() const {
        return iterator(this);
    }
    iterator end() const {
        return iterator();
    }

    // Helper to insert
    void insert(T value) {
        insert_helper(this, value);
    }

private:
    static void insert_helper(binary_tree<T>* node, T value) {
        if ((value) <= (node->data_value)) {
            if (node->left_ptr == nullptr) {
                node->left_ptr = new binary_tree<T>(value);
            } else {
                insert_helper(node->left_ptr, value);
            }
        } else {
            if (node->right_ptr == nullptr) {
                node->right_ptr = new binary_tree<T>(value);
            } else {
                insert_helper(node->right_ptr, value);
            }
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
