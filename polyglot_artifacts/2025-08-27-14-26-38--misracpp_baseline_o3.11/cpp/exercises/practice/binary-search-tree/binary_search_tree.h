#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>  // ensure nullptr_t and related definitions are available
#include <memory>
#include <stack>
#include <iterator>  // std::forward_iterator_tag
#include <utility>   // std::move (needed implicitly by tests)

namespace binary_search_tree {

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int value)
        : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root_(nullptr) {}
    ~BinarySearchTree();

    // Copy constructor
    BinarySearchTree(const BinarySearchTree& other);
    // Copy assignment operator
    BinarySearchTree& operator=(const BinarySearchTree& other);

    // Move constructor
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    // Move assignment operator
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    // Insert a value into the binary search tree.
    void insert(int value);

    // Return true if the value exists in the tree, false otherwise.
    bool contains(int value) const;

private:
    Node* root_;

    // Helper functions
    void insert(Node*& node, int value);
    bool contains(const Node* node, int value) const;
    void clear(Node* node);
    Node* clone(const Node* node) const;
};

/*
 * Generic binary search tree implementation that the tests expect.
 *  - Supports insertion of duplicate keys (duplicates go to the left subtree,
 *    mirroring the <= rule used elsewhere in the code base).
 *  - Provides begin()/end() so the tree can be iterated with a range-for loop
 *    in sorted (in-order) order.
 *  - Exposes left()/right() accessors returning the child unique_ptrs so the
 *    tests can inspect the tree structure.
 */
template <typename T>
class binary_tree {
public:
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value) : data_(value) {}

    // insert a value into the BST
    void insert(const T& value)
    {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    // true if the value exists in the tree
    [[nodiscard]] bool contains(const T& value) const
    {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // accessors used by the unit tests
    [[nodiscard]] const T& data() const { return data_; }
    [[nodiscard]] const tree_ptr& left()  const { return left_;  }
    [[nodiscard]] const tree_ptr& right() const { return right_; }

    // ================= iterator support =================
    // simple in-order traversal iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;          // constructs end()
        explicit iterator(const binary_tree<T>* root) { push_left(root); }

        reference operator*()  const { return stack_.top()->data_; }
        pointer   operator->() const { return &stack_.top()->data_; }

        iterator& operator++()
        {
            const binary_tree<T>* node = stack_.top();
            stack_.pop();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

        friend bool operator==(const iterator& a, const iterator& b)
        {
            if (a.stack_.empty() && b.stack_.empty()) {
                return true;                // both at end()
            }
            if (a.stack_.empty() || b.stack_.empty()) {
                return false;               // only one at end()
            }
            return a.stack_.top() == b.stack_.top(); // compare current nodes
        }
        friend bool operator!=(const iterator& a, const iterator& b)
        {
            return !(a == b);
        }

    private:
        std::stack<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node)
        {
            while (node) {
                stack_.push(node);
                node = node->left_.get();
            }
        }
    };

    [[nodiscard]] iterator begin() const { return iterator(this); }
    [[nodiscard]] iterator end()   const { return iterator();     }

private:
    T data_;
    tree_ptr left_{};
    tree_ptr right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
