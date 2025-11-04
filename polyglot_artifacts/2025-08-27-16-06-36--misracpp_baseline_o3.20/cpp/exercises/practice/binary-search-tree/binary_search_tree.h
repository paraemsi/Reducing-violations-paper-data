#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

// A generic binary search tree node and container.
// Provides insertion, search and in-order iteration.
template <typename T>
class binary_tree {
private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    // Helper to recursively insert.
    void insert_impl(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert_impl(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert_impl(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    // Helper to recursively search.
    bool search_impl(const T& value) const {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->search_impl(value) : false;
        }
        return right_ ? right_->search_impl(value) : false;
    }

public:
    explicit binary_tree(const T& value) : data_(value) {}

    // Disable copy semantics (unique ownership of sub-trees).
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    // Enable default move semantics.
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    // Public interface -----------------------------------------------------

    // Insert a value into the tree.
    void insert(const T& value) { insert_impl(value); }

    // Search for a value in the tree.
    bool search(const T& value) const { return search_impl(value); }

    // Accessors for tests.
    const T& data() const { return data_; }
    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    // Forward iterator for in-order traversal.
    class iterator {
        const binary_tree<T>* current_{nullptr};
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            advance();
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
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

        reference operator*() const { return current_->data_; }
        pointer   operator->() const { return &current_->data_; }

        iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            } else {
                advance();
            }
            return *this;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end()   const { return iterator(); }
};

// (legacy free-function interface removed – functionality now in template)

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
