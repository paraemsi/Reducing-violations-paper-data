#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <stack>
#include <utility>
#include <cstddef>
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
        node(const node&) = delete;
        node& operator=(const node&) = delete;
        ~node() = default;
    };

    using node_ptr = std::unique_ptr<node>;

    binary_tree() : root_(nullptr) {}

    explicit binary_tree(const std::vector<T>& values) : root_(nullptr) {
        for (const auto& v : values) {
            insert(v);
        }
    }

    void insert(const T& value) {
        insert(root_, value);
    }

    bool search(const T& value) const {
        return search(root_.get(), value);
    }

    // For test: data() returns the root value
    const T& data() const {
        return root_->data;
    }

    // For test: left() returns pointer to left subtree, or nullptr
    // For test: left() returns pointer to left subtree, or nullptr
    binary_tree* left() const {
        if (root_ && root_->left) {
            left_holder_ = std::make_unique<binary_tree>();
            left_holder_->root_.reset(root_->left.get());
            return left_holder_.get();
        }
        return nullptr;
    }

    // For test: right() returns pointer to right subtree, or nullptr
    binary_tree* right() const {
        if (root_ && root_->right) {
            right_holder_ = std::make_unique<binary_tree>();
            right_holder_->root_.reset(root_->right.get());
            return right_holder_.get();
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

        explicit iterator(node* root) {
            push_left(root);
        }

        reference operator*() const {
            return stack_.top()->data;
        }

        pointer operator->() const {
            return &(stack_.top()->data);
        }

        iterator& operator++() {
            node* n = stack_.top();
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
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.top() == other.stack_.top();
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<node*> stack_;

        void push_left(node* n) {
            while (n) {
                stack_.push(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const {
        return iterator(root_ ? root_.get() : nullptr);
    }

    iterator end() const {
        return iterator();
    }

private:
    node_ptr root_;

    // These mutable holders are used to return a binary_tree* for left()/right()
    // They are mutable so that left()/right() can be const.
    mutable std::unique_ptr<binary_tree> left_holder_;
    mutable std::unique_ptr<binary_tree> right_holder_;


    void insert(node_ptr& n, const T& value) {
        if (!n) {
            n = std::make_unique<node>(value);
        } else if (value <= n->data) {
            insert(n->left, value);
        } else {
            insert(n->right, value);
        }
    }

    bool search(const node* n, const T& value) const {
        if (!n) return false;
        if (n->data == value) return true;
        if (value < n->data) return search(n->left.get(), value);
        return search(n->right.get(), value);
    }
};

template <typename T>
using tree_ptr = std::unique_ptr<binary_tree<T>>;

template <typename T>
tree_ptr<T> make_tree(const std::vector<T>& data) {
    return std::make_unique<binary_tree<T>>(data);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
