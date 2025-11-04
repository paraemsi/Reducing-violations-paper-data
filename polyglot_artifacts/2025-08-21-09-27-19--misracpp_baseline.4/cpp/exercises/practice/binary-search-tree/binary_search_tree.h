#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <stack>
#include <type_traits>

namespace binary_search_tree {


// Node definition
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;

    explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

// Binary tree definition
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_type = node<T>;

    binary_tree() : root_(nullptr) {}
    explicit binary_tree(const std::vector<T>& values) : root_(nullptr) {
        for (const auto& v : values) {
            insert(v);
        }
    }

    // Disable copy and assignment
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    // Move constructor/assignment
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    void insert(const T& value) {
        insert_impl(root_, value);
    }

    // Search for a value in the tree
    bool search(const T& value) const {
        return search_impl(root_.get(), value);
    }

    // Accessors for test compatibility
    const T& data() const { return root_->data; }
    const binary_tree* left() const {
        if (root_ && root_->left)
            return reinterpret_cast<const binary_tree*>(root_->left.get());
        return nullptr;
    }
    const binary_tree* right() const {
        if (root_ && root_->right)
            return reinterpret_cast<const binary_tree*>(root_->right.get());
        return nullptr;
    }

    // Iterators for in-order traversal
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

        reference operator*() const { return stack_.top()->data; }
        pointer operator->() const { return &(stack_.top()->data); }

        iterator& operator++() {
            const node<T>* n = stack_.top();
            stack_.pop();
            if (n->right)
                push_left(n->right.get());
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.top() == other.stack_.top();
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const node<T>*> stack_;
        void push_left(const node<T>* n) {
            while (n) {
                stack_.push(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const { return iterator(root_.get()); }
    iterator end() const { return iterator(); }

private:
    std::unique_ptr<node<T>> root_;

    void insert_impl(std::unique_ptr<node<T>>& n, const T& value) {
        if (!n) {
            n = std::make_unique<node<T>>(value);
        } else if (value <= n->data) {
            insert_impl(n->left, value);
        } else {
            insert_impl(n->right, value);
        }
    }

    bool search_impl(const node<T>* n, const T& value) const {
        if (!n) return false;
        if (n->data == value) return true;
        if (value < n->data) return search_impl(n->left.get(), value);
        return search_impl(n->right.get(), value);
    }
};

// Helper for test code: make_tree
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    return std::make_unique<binary_tree<T>>(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
