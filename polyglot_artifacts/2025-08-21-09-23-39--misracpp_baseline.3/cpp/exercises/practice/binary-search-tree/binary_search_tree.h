#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace binary_search_tree {

// Forward declaration for template
template <typename T>
class binary_tree;

// Node struct for generic type T
template <typename T>
struct node {
    T data_;
    std::unique_ptr<node<T>> left_;
    std::unique_ptr<node<T>> right_;

    explicit node(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
    node(const node&) = delete;
    node& operator=(const node&) = delete;
    node(node&&) = default;
    node& operator=(node&&) = default;
};

// Binary tree class
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_type = node<T>;
    using node_ptr = std::unique_ptr<node_type>;

    binary_tree() : root_(nullptr) {}
    explicit binary_tree(const std::vector<T>& values) : root_(nullptr) {
        for (const auto& v : values) {
            insert(v);
        }
    }
    ~binary_tree() = default;
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(binary_tree&&) = default;

    void insert(const T& value) {
        insert_impl(root_, value);
    }

    // Returns pointer to left subtree, or nullptr if none
    binary_tree* left() const {
        if (!root_ || !root_->left_) return nullptr;
        left_subtree_ = std::make_unique<binary_tree<T>>();
        left_subtree_->root_ = clone(root_->left_.get());
        return left_subtree_.get();
    }

    // Returns pointer to right subtree, or nullptr if none
    binary_tree* right() const {
        if (!root_ || !root_->right_) return nullptr;
        right_subtree_ = std::make_unique<binary_tree<T>>();
        right_subtree_->root_ = clone(root_->right_.get());
        return right_subtree_.get();
    }

    // Return the data at the root
    const T& data() const {
        return root_->data_;
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
        explicit iterator(const node_type* root) {
            push_left(root);
        }

        reference operator*() const {
            return stack_.back()->data_;
        }

        pointer operator->() const {
            return &(stack_.back()->data_);
        }

        iterator& operator++() {
            const node_type* n = stack_.back();
            stack_.pop_back();
            if (n->right_) {
                push_left(n->right_.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return stack_ == other.stack_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const node_type*> stack_;

        void push_left(const node_type* n) {
            while (n) {
                stack_.push_back(n);
                n = n->left_.get();
            }
        }
    };

    iterator begin() const {
        return iterator(root_.get());
    }

    iterator end() const {
        return iterator();
    }

private:
    node_ptr root_;
    // These are mutable so left()/right() can return a pointer to a subtree
    mutable std::unique_ptr<binary_tree<T>> left_subtree_;
    mutable std::unique_ptr<binary_tree<T>> right_subtree_;

    void insert_impl(node_ptr& n, const T& value) {
        if (!n) {
            n = std::make_unique<node_type>(value);
        } else if (value <= n->data_) {
            insert_impl(n->left_, value);
        } else {
            insert_impl(n->right_, value);
        }
    }

    node_ptr clone(const node_type* n) const {
        if (!n) return nullptr;
        node_ptr new_node = std::make_unique<node_type>(n->data_);
        new_node->left_ = clone(n->left_.get());
        new_node->right_ = clone(n->right_.get());
        return new_node;
    }
};

// Helper function to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    return std::make_unique<binary_tree<T>>(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
