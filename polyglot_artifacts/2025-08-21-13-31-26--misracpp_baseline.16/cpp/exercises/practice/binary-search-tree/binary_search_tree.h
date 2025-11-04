#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <stack>
#include <cstddef>
#include <type_traits>

namespace binary_search_tree {


// Node definition for binary_tree<T>
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;

    explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

// Binary tree class
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_type = node<T>;

    binary_tree() = default;

    // Construct from vector
    explicit binary_tree(const std::vector<T>& values) {
        for (const auto& v : values) {
            insert(v);
        }
    }

    // Insert value into tree
    void insert(const T& value) {
        insert_impl(root, value);
    }

    // Get data at root
    const T& data() const {
        return root->data;
    }

    // Get left subtree
    std::unique_ptr<binary_tree> left() const {
        if (root && root->left) {
            return std::unique_ptr<binary_tree>(new binary_tree(root->left.get()));
        }
        return nullptr;
    }

    // Get right subtree
    std::unique_ptr<binary_tree> right() const {
        if (root && root->right) {
            return std::unique_ptr<binary_tree>(new binary_tree(root->right.get()));
        }
        return nullptr;
    }

    // Iterator for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        explicit iterator(const node<T>* root) {
            push_left(root);
        }

        reference operator*() const {
            return nodes.top()->data;
        }

        pointer operator->() const {
            return &(nodes.top()->data);
        }

        iterator& operator++() {
            const node<T>* n = nodes.top();
            nodes.pop();
            if (n->right) {
                push_left(n->right.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            // std::stack doesn't have operator==, so compare top elements or empty
            if (nodes.empty() && other.nodes.empty()) return true;
            if (nodes.empty() || other.nodes.empty()) return false;
            return nodes.top() == other.nodes.top();
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const node<T>*> nodes;

        void push_left(const node<T>* n) {
            while (n) {
                nodes.push(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const {
        return iterator(root.get());
    }

    iterator end() const {
        return iterator();
    }

private:
    std::unique_ptr<node<T>> root;

    // Helper for copy construction from node pointer
    explicit binary_tree(const node<T>* n) {
        if (n) {
            root = std::make_unique<node<T>>(n->data);
            root->left = clone_subtree(n->left.get());
            root->right = clone_subtree(n->right.get());
        }
    }

    // Helper to deep copy a subtree
    std::unique_ptr<node<T>> clone_subtree(const node<T>* n) const {
        if (!n) return nullptr;
        auto new_node = std::make_unique<node<T>>(n->data);
        new_node->left = clone_subtree(n->left.get());
        new_node->right = clone_subtree(n->right.get());
        return new_node;
    }

    void insert_impl(std::unique_ptr<node<T>>& n, const T& value) {
        if (!n) {
            n = std::make_unique<node<T>>(value);
        } else if (value <= n->data) {
            insert_impl(n->left, value);
        } else {
            insert_impl(n->right, value);
        }
    }

    void insert_subtree(const node<T>* n) {
        if (!n) return;
        insert(n->data);
        insert_subtree(n->left.get());
        insert_subtree(n->right.get());
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
