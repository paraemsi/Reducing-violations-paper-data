#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = typename std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    ~binary_tree() = default;

    const T& data() const { return data_; }

    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }

    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = node_ptr(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = node_ptr(new binary_tree<T>(value));
            }
        }
    }

    // In-order iterator
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

        reference operator*() const { return nodes_.back()->data_; }
        pointer operator->() const { return &(nodes_.back()->data_); }

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
            while (node) {
                nodes_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_{};
    node_ptr left_{nullptr};
    node_ptr right_{nullptr};
};

template <typename T>
typename std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    typename std::unique_ptr<binary_tree<T>> root(new binary_tree<T>(values[0]));
    for (std::size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
