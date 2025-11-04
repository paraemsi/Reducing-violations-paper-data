#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <stack>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    struct node {
        T data;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    using node_type = node;
    using value_type = T;

    binary_tree() = default;

    explicit binary_tree(const std::vector<T>& values) {
        for (const auto& v : values) {
            insert(v);
        }
    }

    void insert(const T& value) {
        insert_impl(root_, value);
    }

    bool search(const T& value) const noexcept {
        return search_impl(root_.get(), value);
    }

    // For test: access to root node
    const node* root() const noexcept { return root_.get(); }

    // For test: data() returns root data
    const T& data() const { return root_->data; }

    // For test: left() returns pointer to left subtree
    std::unique_ptr<binary_tree<T>> left() const {
        if (!root_ || !root_->left) {
            return nullptr;
        }
        auto t = std::make_unique<binary_tree<T>>();
        t->root_ = clone(root_->left.get());
        return t;
    }

    // For test: right() returns pointer to right subtree
    std::unique_ptr<binary_tree<T>> right() const {
        if (!root_ || !root_->right) {
            return nullptr;
        }
        auto t = std::make_unique<binary_tree<T>>();
        t->root_ = clone(root_->right.get());
        return t;
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

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) {
                return true;
            }
            if (stack_.empty() || other.stack_.empty()) {
                return false;
            }
            return stack_.top() == other.stack_.top();
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

    void insert_impl(std::unique_ptr<node>& n, const T& value) {
        if (!n) {
            n = std::make_unique<node>(value);
        } else if (value <= n->data) {
            insert_impl(n->left, value);
        } else {
            insert_impl(n->right, value);
        }
    }

    bool search_impl(const node* n, const T& value) const noexcept {
        if (!n) {
            return false;
        }
        if (value == n->data) {
            return true;
        }
        if (value < n->data) {
            return search_impl(n->left.get(), value);
        }
        return search_impl(n->right.get(), value);
    }

    std::unique_ptr<node> clone(const node* n) const {
        if (!n) {
            return nullptr;
        }
        auto new_node = std::make_unique<node>(n->data);
        new_node->left = clone(n->left.get());
        new_node->right = clone(n->right.get());
        return new_node;
    }
};

// Helper for tests: make_tree
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    return std::make_unique<binary_tree<T>>(data);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
