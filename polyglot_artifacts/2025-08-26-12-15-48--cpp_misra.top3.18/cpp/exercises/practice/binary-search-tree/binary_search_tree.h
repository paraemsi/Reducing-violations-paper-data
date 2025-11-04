#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <algorithm>
#include <utility>

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

    // Accessors for test compatibility
    const T& data() const { return data_; }
    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }

    // In-order iterator support
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) { traverse_left(root); }

        reference operator*() const { return stack_.back()->data_; }
        pointer operator->() const { return &(stack_.back()->data_); }

        iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                traverse_left(node->right_.get());
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
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> stack_;

        void traverse_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
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
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (std::size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
