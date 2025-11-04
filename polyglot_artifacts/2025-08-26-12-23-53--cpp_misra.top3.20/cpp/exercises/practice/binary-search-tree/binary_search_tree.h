#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <type_traits>

namespace binary_search_tree {

using value_type = std::int32_t;

// Node struct for internal use
template <typename T>
struct node {
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;

    explicit node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    node(const node& other)
        : data(other.data)
        , left(other.left ? std::make_unique<node>(*other.left) : nullptr)
        , right(other.right ? std::make_unique<node>(*other.right) : nullptr)
    {}
};

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

    void insert(const T& value) {
        insert_impl(root_, value);
    }

    // Accessors for test compatibility
    const T& data() const { return root_ ? root_->data : throw std::logic_error("empty tree"); }
    const binary_tree* left() const {
        if (root_ && root_->left) {
            return new binary_tree(root_->left.get());
        }
        return nullptr;
    }
    const binary_tree* right() const {
        if (root_ && root_->right) {
            return new binary_tree(root_->right.get());
        }
        return nullptr;
    }

    // Iterator for in-order traversal
    class iterator {
    public:
        iterator() = default;
        explicit iterator(const node_type* root) { push_left(root); }

        const T& operator*() const { return stack_.back()->data; }
        const T* operator->() const { return &(stack_.back()->data); }

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
            return stack_ == other.stack_;
        }
        bool operator!=(const iterator& other) const {
            return !(stack_ == other.stack_);
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

    iterator begin() const { return iterator(root_.get()); }
    iterator end() const { return iterator(); }

    ~binary_tree() = default;

private:
    std::unique_ptr<node_type> root_;

    // Helper for copy construction from node pointer
    explicit binary_tree(const node_type* n) : root_(nullptr) {
        if (n) {
            root_ = std::make_unique<node_type>(*n);
        }
    }

    void insert_impl(std::unique_ptr<node_type>& n, const T& value) {
        if (!n) {
            n = std::make_unique<node_type>(value);
        } else if (value <= n->data) {
            insert_impl(n->left, value);
        } else {
            insert_impl(n->right, value);
        }
    }
};

// Helper for test code: make_tree
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    return std::make_unique<binary_tree<T>>(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
