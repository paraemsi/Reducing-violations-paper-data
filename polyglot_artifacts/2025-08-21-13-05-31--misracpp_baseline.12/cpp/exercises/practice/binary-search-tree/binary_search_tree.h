#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>

namespace binary_search_tree {

template <typename T>
struct binary_tree {
    T value;
    std::unique_ptr<binary_tree<T>> left;
    std::unique_ptr<binary_tree<T>> right;

    explicit binary_tree(const T& v) : value(v), left(nullptr), right(nullptr) {}

    // Insert value into the tree
    void insert(const T& v) {
        if (v <= value) {
            if (left) {
                left->insert(v);
            } else {
                left = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(v));
            }
        } else {
            if (right) {
                right->insert(v);
            } else {
                right = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(v));
            }
        }
    }

    // Search for value in the tree
    bool search(const T& v) const {
        if (v == value) return true;
        if (v < value) {
            return left ? left->search(v) : false;
        } else {
            return right ? right->search(v) : false;
        }
    }

    // Accessors for test compatibility
    const T& data() const { return value; }
    const binary_tree<T>* left_child() const { return left.get(); }
    const binary_tree<T>* right_child() const { return right.get(); }

    // For test compatibility with test code
    const binary_tree<T>* left() const { return left.get(); }
    const binary_tree<T>* right() const { return right.get(); }

    // Iterator for in-order traversal
    struct iterator {
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        std::vector<const binary_tree<T>*> stack;
        const binary_tree<T>* current;

        iterator() : current(nullptr) {}

        explicit iterator(const binary_tree<T>* root) : current(nullptr) {
            // In-order traversal: push all left children to stack
            const binary_tree<T>* n = root;
            while (n) {
                stack.push_back(n);
                n = n->left.get();
            }
            advance();
        }

        void advance() {
            if (stack.empty()) {
                current = nullptr;
                return;
            }
            current = stack.back();
            stack.pop_back();
        }

        iterator& operator++() {
            if (!current) return *this;
            const binary_tree<T>* node = current;
            // Traverse right subtree
            if (node->right) {
                const binary_tree<T>* n = node->right.get();
                while (n) {
                    stack.push_back(n);
                    n = n->left.get();
                }
            }
            advance();
            return *this;
        }

        reference operator*() const { return current->value; }
        pointer operator->() const { return &(current->value); }

        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }
};

// Helper to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) return nullptr;
    std::unique_ptr<binary_tree<T>> root(new binary_tree<T>(data[0]));
    for (size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
