#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <optional>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    // Insert a value into the tree
    void insert(const T& value) {
        if (!data_.has_value()) {
            data_ = value;
            return;
        }
        if (value <= data_.value()) {
            if (!left_) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (!right_) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    // Search for a value in the tree
    bool search(const T& value) const {
        if (!data_.has_value()) {
            return false;
        }
        if (value == data_.value()) {
            return true;
        }
        if (value < data_.value()) {
            return left_ ? left_->search(value) : false;
        } else {
            return right_ ? right_->search(value) : false;
        }
    }

    // Accessors for test code
    const T& data() const { return data_.value(); }
    const binary_tree<T>* left() const { return left_ ? left_.get() : nullptr; }
    const binary_tree<T>* right() const { return right_ ? right_.get() : nullptr; }

    // Iterators for in-order traversal
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

        reference operator*() const { return nodes_.back()->data(); }
        pointer operator->() const { return &(nodes_.back()->data()); }

        iterator& operator++() {
            const binary_tree<T>* node = nodes_.back();
            nodes_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return nodes_ == other.nodes_;
        }
        bool operator!=(const iterator& other) const {
            return nodes_ != other.nodes_;
        }

    private:
        std::vector<const binary_tree<T>*> nodes_;

        void push_left(const binary_tree<T>* node) {
            while (node && node->data_.has_value()) {
                nodes_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    std::optional<T> data_;
    node_ptr left_;
    node_ptr right_;
};

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
