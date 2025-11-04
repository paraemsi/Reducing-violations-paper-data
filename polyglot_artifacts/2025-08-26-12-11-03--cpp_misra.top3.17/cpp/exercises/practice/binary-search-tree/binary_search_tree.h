#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& v) : value_(v), has_value_(true) {}

    // Insert a value into the tree
    void insert(const T& v) {
        if (!has_value_) {
            value_ = v;
            has_value_ = true;
            return;
        }
        if (v <= value_) {
            if (!left_) {
                left_ = std::make_unique<binary_tree<T>>(v);
            } else {
                left_->insert(v);
            }
        } else {
            if (!right_) {
                right_ = std::make_unique<binary_tree<T>>(v);
            } else {
                right_->insert(v);
            }
        }
    }

    // Search for a value in the tree
    bool search(const T& v) const {
        if (!has_value_) {
            return false;
        }
        if (v == value_) {
            return true;
        }
        if (v < value_) {
            return left_ ? left_->search(v) : false;
        } else {
            return right_ ? right_->search(v) : false;
        }
    }

    // Data access
    const T& data() const { return value_; }

    // Left/right access
    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }

    // Iteration (in-order)
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) {
            push_left(root);
        }

        reference operator*() const { return nodes_.back()->value_; }
        pointer operator->() const { return &(nodes_.back()->value_); }

        iterator& operator++() {
            const binary_tree<T>* node = nodes_.back();
            nodes_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int dummy) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return nodes_ == other.nodes_;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> nodes_;
        void push_left(const binary_tree<T>* node) {
            while ((node != nullptr) && (node->has_value_)) {
                nodes_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

    bool has_value() const { return has_value_; }

private:
    T value_{};
    bool has_value_ = false;
    node_ptr left_{};
    node_ptr right_{};
};

// Helper to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    auto tree = std::make_unique<binary_tree<T>>();
    for (const auto& v : data) {
        tree->insert(v);
    }
    return tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
