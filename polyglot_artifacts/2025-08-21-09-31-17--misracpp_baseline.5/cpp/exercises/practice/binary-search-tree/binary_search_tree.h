#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <stack>
#include <cstddef>
#include <type_traits>

namespace binary_search_tree {


// Node struct for internal use
template <typename T>
struct node {
    T data;
    node* left;
    node* right;

    explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    node(const node& other) : data(other.data), left(nullptr), right(nullptr) {
        if (other.left) left = new node(*other.left);
        if (other.right) right = new node(*other.right);
    }
    ~node() {
        delete left;
        delete right;
    }
};

// Binary tree class
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_type = node<T>;

    binary_tree() : root_(nullptr) {}
    binary_tree(const binary_tree& other) : root_(nullptr) {
        if (other.root_) {
            root_ = new node_type(*other.root_);
        }
    }
    ~binary_tree() { delete root_; }

    // Insert a value into the tree
    void insert(const T& value) {
        insert(root_, value);
    }

    // Search for a value in the tree
    bool search(const T& value) const {
        return search(root_, value);
    }

    // Get the data at the root
    const T& data() const {
        return root_->data;
    }

    // Get left subtree
    binary_tree* left() const {
        if (root_ && root_->left) {
            return new binary_tree(root_->left);
        }
        return nullptr;
    }

    // Get right subtree
    binary_tree* right() const {
        if (root_ && root_->right) {
            return new binary_tree(root_->right);
        }
        return nullptr;
    }

    // Iterator for in-order traversal
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() : current_(nullptr) {}

        explicit iterator(node_type* root) {
            current_ = nullptr;
            push_left(root);
            advance();
        }

        reference operator*() const { return current_->data; }
        pointer operator->() const { return &(current_->data); }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            advance();
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        node_type* current_;
        std::stack<node_type*> stack_;

        void push_left(node_type* node) {
            while (node) {
                stack_.push(node);
                node = node->left;
            }
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.top();
            stack_.pop();
            push_left(current_->right);
        }
    };

    iterator begin() const {
        return iterator(root_);
    }

    iterator end() const {
        return iterator();
    }

private:
    node_type* root_;

    // Private constructor for subtree
    explicit binary_tree(node_type* n) : root_(nullptr) {
        if (n) {
            root_ = new node_type(*n);
        }
    }

    // Remove clone function, as copy constructor is now used

    void insert(node_type*& n, const T& value) {
        if (!n) {
            n = new node_type(value);
        } else if (value < n->data) {
            insert(n->left, value);
        } else {
            insert(n->right, value);
        }
    }

    bool search(const node_type* n, const T& value) const {
        if (!n) return false;
        if (n->data == value) return true;
        if (value < n->data) return search(n->left, value);
        return search(n->right, value);
    }
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    auto tree = std::make_unique<binary_tree<T>>();
    for (const auto& x : data) {
        tree->insert(x);
    }
    return tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
