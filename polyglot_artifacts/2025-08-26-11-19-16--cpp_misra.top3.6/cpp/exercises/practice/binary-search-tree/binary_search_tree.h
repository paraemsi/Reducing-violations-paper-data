#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <stack>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    struct node {
        value_type data;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        explicit node(const value_type& val) : data(val), left(), right() {}
    };

    binary_tree() : root_() {}

    explicit binary_tree(const std::vector<value_type>& values) : root_() {
        for (const auto& v : values) {
            insert(v);
        }
    }

    void insert(const value_type& val) {
        insert_impl(root_, val);
    }

    bool search(const value_type& val) const {
        return search_impl(root_.get(), val);
    }

    // Accessors for test compatibility
    const value_type& data() const { return root_->data; }
    const binary_tree* left() const { return (root_ && root_->left) ? new binary_tree(root_->left.get()) : nullptr; }
    const binary_tree* right() const { return (root_ && root_->right) ? new binary_tree(root_->right.get()) : nullptr; }

    // Iterators for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        iterator() = default;

        explicit iterator(const node* root) {
            push_left(root);
        }

        reference operator*() const { return stack_.top()->data; }
        pointer operator->() const { return &(stack_.top()->data); }

        iterator& operator++() {
            const node* n = stack_.top();
            stack_.pop();
            if (n->right) {
                push_left(n->right.get());
            }
            return *this;
        }

        iterator operator++(int dummy) {
            iterator tmp = *this;
            ++(*this);
            (void)dummy; // suppress unused warning
            return tmp;
        }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) { return true; }
            if (stack_.empty() || other.stack_.empty()) { return false; }
            return (stack_.top() == other.stack_.top());
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const node*> stack_;

        void push_left(const node* n) {
            while (n) {
                stack_.push(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const { return iterator(root_.get()); }
    iterator end() const { return iterator(); }

private:
    std::unique_ptr<node> root_;

    // Helper constructor for left/right accessors (non-owning, for test access)
    explicit binary_tree(const node* n) : root_() {
        if (n) {
            root_ = std::make_unique<node>(n->data);
            if (n->left) {
                root_->left = clone_subtree(n->left.get());
            }
            if (n->right) {
                root_->right = clone_subtree(n->right.get());
            }
        }
    }

    static std::unique_ptr<node> clone_subtree(const node* n) {
        if (!n) return nullptr;
        auto new_node = std::make_unique<node>(n->data);
        new_node->left = clone_subtree(n->left.get());
        new_node->right = clone_subtree(n->right.get());
        return new_node;
    }

    void insert_impl(std::unique_ptr<node>& n, const value_type& val) {
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

// Helper for test compatibility
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    return std::make_unique<binary_tree<T>>(data);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
