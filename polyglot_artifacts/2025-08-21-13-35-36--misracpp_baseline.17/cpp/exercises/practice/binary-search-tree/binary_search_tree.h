#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <cstddef>
#include <utility>
#include <vector>

namespace binary_search_tree {

template <typename T>
struct binary_tree {
    T value;
    std::unique_ptr<binary_tree<T>> left;
    std::unique_ptr<binary_tree<T>> right;

    explicit binary_tree(const T& v) : value(v), left(nullptr), right(nullptr) {}

    // Insert a value into the tree
    void insert(const T& v) {
        if (v <= value) {
            if (left) {
                left->insert(v);
            } else {
                left = std::make_unique<binary_tree<T>>(v);
            }
        } else {
            if (right) {
                right->insert(v);
            } else {
                right = std::make_unique<binary_tree<T>>(v);
            }
        }
    }

    // Search for a value in the tree
    bool search(const T& v) const {
        if (v == value) {
            return true;
        } else if (v < value) {
            return left ? left->search(v) : false;
        } else {
            return right ? right->search(v) : false;
        }
    }

    // Accessors for test compatibility
    const T& data() const { return value; }
    const binary_tree<T>* left_node() const { return left.get(); }
    const binary_tree<T>* right_node() const { return right.get(); }

    // For test compatibility: left() and right() return pointer or nullptr
    const binary_tree<T>* left() const { return left.get(); }
    const binary_tree<T>* right() const { return right.get(); }

    // Iterator for in-order traversal
    struct iterator {
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) {
            push_left(root);
        }

        reference operator*() const { return node_stack.back()->value; }
        pointer operator->() const { return &(node_stack.back()->value); }

        iterator& operator++() {
            const binary_tree<T>* node = node_stack.back();
            node_stack.pop_back();
            if (node->right) {
                push_left(node->right.get());
            }
            return *this;
        }

        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& other) const {
            return node_stack == other.node_stack;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> node_stack;

        void push_left(const binary_tree<T>* node) {
            while (node) {
                node_stack.push_back(node);
                node = node->left.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }
};

// Helper function to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) return nullptr;
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
