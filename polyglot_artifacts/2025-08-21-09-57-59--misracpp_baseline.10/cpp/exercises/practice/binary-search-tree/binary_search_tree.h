#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <stdexcept>

namespace binary_search_tree {


// Node struct for generic type T
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;

    explicit node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    node(const node& other)
        : data(other.data)
        , left(other.left ? std::make_unique<node<T>>(*other.left) : nullptr)
        , right(other.right ? std::make_unique<node<T>>(*other.right) : nullptr)
    {}
    node& operator=(const node& other) {
        if (this != &other) {
            data = other.data;
            left = other.left ? std::make_unique<node<T>>(*other.left) : nullptr;
            right = other.right ? std::make_unique<node<T>>(*other.right) : nullptr;
        }
        return *this;
    }
};

// Binary tree class
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_type = node<T>;
    using pointer = node_type*;
    using const_pointer = const node_type*;

    binary_tree() = default;

    // Construct from vector
    explicit binary_tree(const std::vector<T>& values) {
        for (const auto& v : values) {
            insert(v);
        }
    }

    // Insert a value into the BST
    void insert(const T& value) {
        if (!root_) {
            root_ = std::make_unique<node_type>(value);
        } else {
            insert_impl(root_.get(), value);
        }
    }

    // Get the data at the root
    const T& data() const {
        if (!root_) throw std::logic_error("empty tree");
        return root_->data;
    }

    // Get left subtree
    std::unique_ptr<binary_tree<T>> left() const {
        if (root_ && root_->left) {
            auto t = std::make_unique<binary_tree<T>>();
            t->root_ = std::make_unique<node_type>(*root_->left);
            return t;
        }
        return nullptr;
    }

    // Get right subtree
    std::unique_ptr<binary_tree<T>> right() const {
        if (root_ && root_->right) {
            auto t = std::make_unique<binary_tree<T>>();
            t->root_ = std::make_unique<node_type>(*root_->right);
            return t;
        }
        return nullptr;
    }

    // In-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(const node_type* root) {
            push_left(root);
        }

        reference operator*() const { return stack_.back()->data; }
        pointer operator->() const { return &(stack_.back()->data); }

        iterator& operator++() {
            const node_type* n = stack_.back();
            stack_.pop_back();
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
            // Both empty
            if (stack_.empty() && other.stack_.empty()) return true;
            // Both non-empty and point to same node
            if (!stack_.empty() && !other.stack_.empty())
                return stack_.back() == other.stack_.back();
            // One empty, one not
            return false;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const node_type*> stack_;

        void push_left(const node_type* n) {
            while (n) {
                stack_.push_back(n);
                n = n->left.get();
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
    std::unique_ptr<node_type> root_;

    void insert_impl(node_type* n, const T& value) {
        if (value <= n->data) {
            if (n->left) {
                insert_impl(n->left.get(), value);
            } else {
                n->left = std::make_unique<node_type>(value);
            }
        } else {
            if (n->right) {
                insert_impl(n->right.get(), value);
            } else {
                n->right = std::make_unique<node_type>(value);
            }
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
