#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <stack>
#include <vector>
#include <cstddef>

namespace binary_search_tree {


// Node definition
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;

    explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    // Disable copy and assignment
    node(const node& other)
        : data(other.data)
        , left(other.left ? std::make_unique<node>(*other.left) : nullptr)
        , right(other.right ? std::make_unique<node>(*other.right) : nullptr)
    {}
    node& operator=(const node& other) {
        if (this != &other) {
            data = other.data;
            left = other.left ? std::make_unique<node>(*other.left) : nullptr;
            right = other.right ? std::make_unique<node>(*other.right) : nullptr;
        }
        return *this;
    }
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
    // Move constructor/assignment
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    // No copy
    binary_tree(const binary_tree& other) : root_(nullptr) {
        if (other.root_) {
            root_ = std::make_unique<node_type>(*other.root_);
        }
    }
    binary_tree& operator=(const binary_tree& other) {
        if (this != &other) {
            if (other.root_) {
                root_ = std::make_unique<node_type>(*other.root_);
            } else {
                root_.reset();
            }
        }
        return *this;
    }

    void insert(const T& value) {
        insert_impl(root_, value);
    }

    // Search for a value
    bool search(const T& value) const {
        node_type* cur = root_.get();
        while (cur) {
            if (value == cur->data) return true;
            if (value < cur->data) cur = cur->left.get();
            else cur = cur->right.get();
        }
        return false;
    }

    // Accessors for tests
    const T& data() const { return root_->data; }
    // The returned pointer must be deleted by the caller (test code).
    const binary_tree* left() const {
        if (root_ && root_->left) {
            return new binary_tree(*root_->left);
        }
        return nullptr;
    }
    const binary_tree* right() const {
        if (root_ && root_->right) {
            return new binary_tree(*root_->right);
        }
        return nullptr;
    }

    // Iterator for in-order traversal
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(node_type* root) {
            push_left(root);
        }

        reference operator*() const { return stack_.top()->data; }
        pointer operator->() const { return &(stack_.top()->data); }

        iterator& operator++() {
            node_type* n = stack_.top();
            stack_.pop();
            if (n->right) push_left(n->right.get());
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
        std::stack<node_type*> stack_;
        void push_left(node_type* n) {
            while (n) {
                stack_.push(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const { return iterator(root_.get()); }
    iterator end() const { return iterator(); }

private:
    std::unique_ptr<node_type> root_;

    void insert_impl(std::unique_ptr<node_type>& node, const T& value) {
        if (!node) {
            node = std::make_unique<node_type>(value);
        } else if (value <= node->data) {
            insert_impl(node->left, value);
        } else {
            insert_impl(node->right, value);
        }
    }
};

// Helper for tests: make_tree
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    return std::make_unique<binary_tree<T>>(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
