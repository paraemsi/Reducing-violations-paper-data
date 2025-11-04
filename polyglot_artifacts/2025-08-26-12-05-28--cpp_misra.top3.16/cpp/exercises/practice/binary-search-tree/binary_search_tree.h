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
    using value_type = T;

    struct node {
        value_type data;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        explicit node(const value_type& value)
            : data(value), left(), right() {}
    };

    binary_tree() : root_() {}

    explicit binary_tree(const std::vector<value_type>& values) : root_() {
        for (const auto& v : values) {
            insert(v);
        }
    }

    void insert(const value_type& value) {
        insert_impl(root_, value);
    }

    bool search(const value_type& value) const {
        return search_impl(root_.get(), value);
    }

    // For test: access to root node data
    const value_type& data() const { return root_->data; }
    const binary_tree* left() const { return root_->left ? new binary_tree(*(root_->left)) : nullptr; }
    const binary_tree* right() const { return root_->right ? new binary_tree(*(root_->right)) : nullptr; }

    // Iterators for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() : current_(nullptr), value_(nullptr) {}

        explicit iterator(const node* root) : current_(nullptr), value_(nullptr) {
            push_left(root);
            advance();
        }

        reference operator*() const { return *value_; }
        pointer operator->() const { return value_; }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return (current_ == other.current_) && (value_ == other.value_);
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        const node* current_;
        std::stack<const node*> stack_;
        const value_type* value_;

        void push_left(const node* n) {
            while (n) {
                stack_.push(n);
                n = n->left.get();
            }
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                value_ = nullptr;
                return;
            }
            current_ = stack_.top();
            stack_.pop();
            value_ = &(current_->data);
            if (current_->right) {
                push_left(current_->right.get());
            }
        }
    };

    iterator begin() const { return iterator(root_.get()); }
    iterator end() const { return iterator(); }

private:
    std::unique_ptr<node> root_;

    // Helper constructor for left()/right() test API
    binary_tree(const node& n) : root_() {
        insert(n.data);
        if (n.left) {
            insert_subtree(*(n.left));
        }
        if (n.right) {
            insert_subtree(*(n.right));
        }
    }

    void insert_subtree(const node& n) {
        insert(n.data);
        if (n.left) insert_subtree(*(n.left));
        if (n.right) insert_subtree(*(n.right));
    }

    void insert_impl(std::unique_ptr<node>& n, const value_type& value) {
        if (!n) {
            n = std::make_unique<node>(value);
        } else if (value <= n->data) {
            insert_impl(n->left, value);
        } else {
            insert_impl(n->right, value);
        }
    }

    bool search_impl(const node* n, const value_type& value) const {
        if (!n) {
            return false;
        }
        if (value == n->data) {
            return true;
        } else if (value < n->data) {
            return search_impl(n->left.get(), value);
        } else {
            return search_impl(n->right.get(), value);
        }
    }
};

// Helper for test code
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    return std::make_unique<binary_tree<T>>(data);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
