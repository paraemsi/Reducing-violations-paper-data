#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <memory>
#include <stack>
#include <iterator>

namespace binary_search_tree {

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int value) : data{value}, left{nullptr}, right{nullptr} {}

    /* Disable copy and move operations to avoid double-free issues. */
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;

    /*  Recursively delete sub-trees to avoid memory leaks. */
    ~Node() noexcept {
        delete left;
        delete right;
        left = right = nullptr;    // avoid dangling pointers
    }
};

/*  Insert value into the tree.
    If root is nullptr, a new Node is created and root now points to it.
*/
void insert(Node*& root, int value);

/*  Return true if value exists in the tree, false otherwise. */
bool contains(const Node* root, int value);

/* --------------------------------------------------------------------------
 * Template binary search tree used by the exercise tests.
 * ------------------------------------------------------------------------*/
template <typename T>
class binary_tree {
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
    T data_;


public:
    explicit binary_tree(const T& value)
        : left_{nullptr}, right_{nullptr}, data_{value} {}

    /* Disable copy – tree owns its children uniquely. */
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    /* Default move operations. */
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    /* Accessors */
    const T& data() const { return data_; }

    binary_tree<T>* left() { return left_.get(); }
    const binary_tree<T>* left() const { return left_.get(); }

    binary_tree<T>* right() { return right_.get(); }
    const binary_tree<T>* right() const { return right_.get(); }

    /* Insert respecting exercise rule: duplicates go to the left. */
    void insert(const T& value) {
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

    bool contains(const T& value) const {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    /* Forward iterator producing in-order traversal. */
    class iterator {
        std::stack<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push(node);
                node = node->left();
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) { push_left(root); }

        reference operator*() const { return stack_.top()->data(); }
        pointer   operator->() const { return &stack_.top()->data(); }

        iterator& operator++() {
            const binary_tree<T>* node = stack_.top();
            stack_.pop();
            if (node->right()) {
                push_left(node->right());
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.top() == other.stack_.top();
        }
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    iterator begin() const { return iterator(this); }
    iterator end()   const { return iterator(); }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
