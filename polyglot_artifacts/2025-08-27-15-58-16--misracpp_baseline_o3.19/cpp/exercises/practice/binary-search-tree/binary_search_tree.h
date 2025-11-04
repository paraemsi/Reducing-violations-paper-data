#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <initializer_list>

namespace binary_search_tree {

// -----------------------------------------------------------------------------
// A lightweight templated binary search tree used by the unit-tests.
// -----------------------------------------------------------------------------
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : data_(value) {}

    // non-copyable, movable
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    // insert while keeping BST ordering
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }

    // accessors ---------------------------------------------------------------
    const T& data() const { return data_; }
    const std::unique_ptr<binary_tree>& left()  const { return left_;  }
    const std::unique_ptr<binary_tree>& right() const { return right_; }

    // iterator (in-order traversal) ------------------------------------------
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;
        explicit iterator(const binary_tree* node) { push_left(node); }

        reference operator*()  const { return stack_.back()->data_; }
        pointer   operator->() const { return &stack_.back()->data_; }

        iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

        bool operator==(const iterator& other) const {
            return current() == other.current();
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree*> stack_;

        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        const binary_tree* current() const {
            return stack_.empty() ? nullptr : stack_.back();
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end()   const { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree> left_{};
    std::unique_ptr<binary_tree> right_{};
};

// -----------------------------------------------------------------------------
// Helper factory used by the unit-tests
// -----------------------------------------------------------------------------
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(values.front());
    for (auto it = std::next(values.begin()); it != values.end(); ++it) {
        root->insert(*it);
    }
    return root;
}

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> values) {
    return make_tree(std::vector<T>(values));
}

// -----------------------------------------------------------------------------
// Legacy non-templated BinarySearchTree preserved for binary_search_tree.cpp
// -----------------------------------------------------------------------------
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    // Non-copyable
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Movable
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    // Insert a value into the tree
    void insert(int value);

    // Check whether a value exists in the tree
    bool contains(int value) const;

private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        explicit Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root_ = nullptr;

    // Helper functions
    static Node* insert(Node* node, int value);
    static bool contains(const Node* node, int value);
    static void destroy(Node* node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
