#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace binary_search_tree {


// Node definition
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;

    explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    node(const node& other)
        : data(other.data)
        , left(other.left ? std::make_unique<node>(*other.left) : nullptr)
        , right(other.right ? std::make_unique<node>(*other.right) : nullptr)
    {}
};

// Binary tree definition
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_type = node<T>;

    binary_tree() = default;
    explicit binary_tree(const T& value) : root_(std::make_unique<node_type>(value)) {}
    // Construct from node pointer (for left/right)
    explicit binary_tree(const node_type* n) {
        if (n) {
            root_ = std::make_unique<node_type>(n->data);
            if (n->left)
                root_->left = std::make_unique<node_type>(*n->left);
            if (n->right)
                root_->right = std::make_unique<node_type>(*n->right);
        }
    }

    // Insert a value into the tree
    void insert(const T& value) {
        insert_impl(root_, value);
    }

    // Search for a value in the tree
    bool search(const T& value) const {
        return search_impl(root_.get(), value);
    }

    // Get the data at the root
    const T& data() const {
        if (!root_) throw std::logic_error("Empty tree has no data");
        return root_->data;
    }

    // Get left subtree
    binary_tree* left() const {
        if (root_ && root_->left)
            return new binary_tree(root_->left.get());
        return nullptr;
    }

    // Get right subtree
    binary_tree* right() const {
        if (root_ && root_->right)
            return new binary_tree(root_->right.get());
        return nullptr;
    }

    // Iterator for in-order traversal
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        explicit iterator(const node_type* root) { push_left(root); }

        reference operator*() const { return stack_.empty() ? throw std::out_of_range("Iterator out of range") : stack_.back()->data; }
        pointer operator->() const { return stack_.empty() ? throw std::out_of_range("Iterator out of range") : &(stack_.back()->data); }

        iterator& operator++() {
            if (stack_.empty()) return *this;
            const node_type* n = stack_.back();
            stack_.pop_back();
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
            return stack_.back() == other.stack_.back();
        }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        std::vector<const node_type*> stack_;

        void push_left(const node_type* n) {
            while (n) {
                stack_.push_back(n);
                n = n->left.get();
            }
        }
    };

    iterator begin() const { return iterator(root_.get()); }
    iterator end() const { return iterator(); }

private:
    std::unique_ptr<node_type> root_;

    void insert_impl(std::unique_ptr<node_type>& n, const T& value) {
        if (!n) {
            n = std::make_unique<node_type>(value);
        } else if (value <= n->data) {
            insert_impl(n->left, value);
        } else {
            insert_impl(n->right, value);
        }
    }

    bool search_impl(const node_type* n, const T& value) const {
        if (!n) return false;
        if (n->data == value) return true;
        if (value < n->data) return search_impl(n->left.get(), value);
        return search_impl(n->right.get(), value);
    }
};

// Helper function to build a tree from a vector
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
