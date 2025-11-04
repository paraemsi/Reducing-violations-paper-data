#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <cstddef>   // std::ptrdiff_t

namespace binary_search_tree {

// A simple binary search tree that stores integers and supports
// insertion and look-up (contains).
class BinarySearchTree {
public:
    BinarySearchTree() = default;

    // Deep-copy constructor / assignment
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);

    // Move constructor / assignment
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    ~BinarySearchTree();

    // Insert a new value into the tree.  Duplicate values are ignored.
    void insert(int value);

    // Return true if value is present in the tree, otherwise false.
    [[nodiscard]] bool contains(int value) const;

private:
    struct Node {
        int   value;
        Node* left  = nullptr;
        Node* right = nullptr;

        explicit Node(int v) : value(v) {}
    };

    Node* root_ = nullptr;

    // Internal helpers
    static Node* insert(Node* node, int value);
    static bool  contains(const Node* node, int value);
    static void  destroy(Node* node);
    static Node* clone(const Node* node);   // helper for deep copy
};

// ---------------------------------------------------------------------------
// A templated binary search tree used by the unit-tests below
// ---------------------------------------------------------------------------
template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_{value} {}

    // disable copying/moving for simplicty – the tests use unique_ptr
    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&)                 = delete;
    binary_tree& operator=(binary_tree&&)      = delete;

    // Insert (duplicates are allowed – they go to the left subtree)
    void insert(const T& v) {
        if (v <= value_) {
            if (left_) {
                left_->insert(v);
            } else {
                left_ = std::make_unique<binary_tree>(v);
            }
        } else {
            if (right_) {
                right_->insert(v);
            } else {
                right_ = std::make_unique<binary_tree>(v);
            }
        }
    }

    // Accessors ----------------------------------------------------------------
    // Value accessor
    const T& data() const { return value_; }

    // Child accessors
    binary_tree*       left()        { return left_.get(); }
    const binary_tree* left()  const { return left_.get(); }

    binary_tree*       right()       { return right_.get(); }
    const binary_tree* right() const { return right_.get(); }

    // In-order iterator --------------------------------------------------------
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;
        explicit iterator(binary_tree* root) { push_left(root); }

        reference operator*()  const { return stack_.back()->value_; }
        pointer   operator->() const { return &stack_.back()->value_; }

        iterator& operator++() {
            binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right()) {
                push_left(node->right());
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const iterator& a, const iterator& b) {
            if (a.stack_.empty() && b.stack_.empty()) return true;
            if (a.stack_.empty() || b.stack_.empty()) return false;
            return a.stack_.back() == b.stack_.back();
        }
        friend bool operator!=(const iterator& a, const iterator& b) { return !(a == b); }

    private:
        std::vector<binary_tree*> stack_;
        void push_left(binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left();
            }
        }
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;
        explicit const_iterator(const binary_tree* root) { push_left(root); }

        reference operator*()  const { return stack_.back()->value_; }
        pointer   operator->() const { return &stack_.back()->value_; }

        const_iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right()) {
                push_left(node->right());
            }
            return *this;
        }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const const_iterator& a, const const_iterator& b) {
            if (a.stack_.empty() && b.stack_.empty()) return true;
            if (a.stack_.empty() || b.stack_.empty()) return false;
            return a.stack_.back() == b.stack_.back();
        }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) { return !(a == b); }

    private:
        std::vector<const binary_tree*> stack_;
        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left();
            }
        }
    };

    iterator       begin()       { return iterator(this); }
    iterator       end()         { return iterator(); }
    const_iterator begin() const { return const_iterator(this); }
    const_iterator end()   const { return const_iterator(); }

private:
    T value_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
