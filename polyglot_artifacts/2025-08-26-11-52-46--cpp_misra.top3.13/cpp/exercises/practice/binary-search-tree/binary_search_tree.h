#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    struct node {
        value_type data;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        explicit node(const value_type& val) : data(val), left(nullptr), right(nullptr) {}
    };
    using node_ptr = std::unique_ptr<node>;

    binary_tree() : root(nullptr) {}

    explicit binary_tree(const std::vector<value_type>& values) : root(nullptr) {
        for (const auto& v : values) {
            insert(v);
        }
    }

    void insert(const value_type& val) {
        insert_impl(root, val);
    }

    bool search(const value_type& val) const {
        return search_impl(root.get(), val);
    }

    // Accessors for test compatibility
    const value_type& data() const { return root->data; }
    const binary_tree* left() const { return root && root->left ? new binary_tree(*this, root->left.get()) : nullptr; }
    const binary_tree* right() const { return root && root->right ? new binary_tree(*this, root->right.get()) : nullptr; }

    // Iterator for in-order traversal
    class iterator {
    public:
        iterator() = default;
        explicit iterator(const node* root) { push_left(root); }

        const value_type& operator*() const { return stack.back()->data; }
        const value_type* operator->() const { return &(stack.back()->data); }

        iterator& operator++() {
            const node* n = stack.back();
            stack.pop_back();
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
            return stack == other.stack;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const node*> stack;
        void push_left(const node* n) {
            while (n) {
                stack.push_back(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const { return iterator(root.get()); }
    iterator end() const { return iterator(); }

private:
    node_ptr root;

    // For test compatibility: allow constructing a view on a subtree
    binary_tree(const binary_tree& /*parent*/, const node* subroot)
        : root(nullptr)
    {
        if (subroot) {
            copy_subtree(subroot, root);
        }
    }

    void copy_subtree(const node* src, node_ptr& dest) {
        if (!src) {
            dest = nullptr;
            return;
        }
        dest = std::make_unique<node>(src->data);
        if (src->left) {
            copy_subtree(src->left.get(), dest->left);
        }
        if (src->right) {
            copy_subtree(src->right.get(), dest->right);
        }
    }

    void insert_impl(node_ptr& n, const value_type& val) {
        if (!n) {
            n = std::make_unique<node>(val);
        } else if (val <= n->data) {
            insert_impl(n->left, val);
        } else {
            insert_impl(n->right, val);
        }
    }

    bool search_impl(const node* n, const value_type& val) const {
        if (!n) { return false; }
        if (val == n->data) { return true; }
        if (val < n->data) { return search_impl(n->left.get(), val); }
        return search_impl(n->right.get(), val);
    }
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    return std::make_unique<binary_tree<T>>(data);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
