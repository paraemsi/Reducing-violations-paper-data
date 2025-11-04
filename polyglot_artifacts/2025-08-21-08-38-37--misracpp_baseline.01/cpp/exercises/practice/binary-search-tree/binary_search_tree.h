#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <cstddef>
#include <utility>

namespace binary_search_tree {


// Node definition
template <typename T>
struct node {
    T data_;
    std::unique_ptr<node<T>> left_;
    std::unique_ptr<node<T>> right_;

    explicit node(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
};

// Binary tree definition
template <typename T>
class binary_tree {
public:
    using node_type = node<T>;
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() : root_(nullptr) {}
    explicit binary_tree(const T& value) : root_(std::make_unique<node_type>(value)) {}

    // Insert value into the tree
    void insert(const T& value) {
        insert_impl(root_, value);
    }

    // Get data at root
    const T& data() const {
        return root_->data_;
    }

    // Get left subtree
    tree_ptr& left() {
        if (!root_ || !root_->left_) {
            static tree_ptr empty;
            return empty;
        }
        if (!left_tree_) {
            left_tree_ = std::make_unique<binary_tree<T>>();
            copy_subtree(left_tree_->root_, root_->left_);
        }
        return left_tree_;
    }
    const tree_ptr& left() const {
        if (!root_ || !root_->left_) {
            static tree_ptr empty;
            return empty;
        }
        if (!left_tree_) {
            auto* self = const_cast<binary_tree<T>*>(this);
            self->left_tree_ = std::make_unique<binary_tree<T>>();
            copy_subtree(self->left_tree_->root_, root_->left_);
        }
        return left_tree_;
    }

    // Get right subtree
    tree_ptr& right() {
        if (!root_ || !root_->right_) {
            static tree_ptr empty;
            return empty;
        }
        if (!right_tree_) {
            right_tree_ = std::make_unique<binary_tree<T>>();
            copy_subtree(right_tree_->root_, root_->right_);
        }
        return right_tree_;
    }
    const tree_ptr& right() const {
        if (!root_ || !root_->right_) {
            static tree_ptr empty;
            return empty;
        }
        if (!right_tree_) {
            auto* self = const_cast<binary_tree<T>*>(this);
            self->right_tree_ = std::make_unique<binary_tree<T>>();
            copy_subtree(self->right_tree_->root_, root_->right_);
        }
        return right_tree_;
    }

    // Iterator for in-order traversal
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr) {}
        explicit iterator(node_type* root) { traverse_left(root); }

        iterator& operator++() {
            if (stack_.empty()) {
                current_ = nullptr;
                return *this;
            }
            node_type* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                traverse_left(node->right_.get());
            }
            if (!stack_.empty()) {
                current_ = stack_.back();
            } else {
                current_ = nullptr;
            }
            return *this;
        }

        reference operator*() const {
            return current_->data_;
        }

        bool operator!=(const iterator& other) const {
            return current_ != other.current_;
        }

    private:
        node_type* current_ = nullptr;
        std::vector<node_type*> stack_;

        void traverse_left(node_type* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            if (!stack_.empty()) {
                current_ = stack_.back();
            } else {
                current_ = nullptr;
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
    mutable tree_ptr left_tree_;
    mutable tree_ptr right_tree_;

    void insert_impl(std::unique_ptr<node_type>& node, const T& value) {
        if (!node) {
            node = std::make_unique<node_type>(value);
        } else if (value <= node->data_) {
            insert_impl(node->left_, value);
        } else {
            insert_impl(node->right_, value);
        }
    }

    // Helper to deep copy a subtree
    static void copy_subtree(std::unique_ptr<node_type>& dest, const std::unique_ptr<node_type>& src) {
        if (!src) {
            dest.reset();
            return;
        }
        dest = std::make_unique<node_type>(src->data_);
        if (src->left_) {
            copy_subtree(dest->left_, src->left_);
        }
        if (src->right_) {
            copy_subtree(dest->right_, src->right_);
        }
    }
};

// Helper to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) return nullptr;
    auto tree = std::make_unique<binary_tree<T>>();
    for (const auto& x : data) {
        tree->insert(x);
    }
    return tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
