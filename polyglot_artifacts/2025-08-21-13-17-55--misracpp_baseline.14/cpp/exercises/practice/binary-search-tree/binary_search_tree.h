#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <stack>
#include <utility>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    const T& data() const { return data_; }

    const ptr& left() const { return left_; }
    const ptr& right() const { return right_; }

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

    // In-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(const binary_tree* root) {
            push_left(root);
        }

        reference operator*() const {
            return nodes_.top()->data_;
        }

        pointer operator->() const {
            return &(nodes_.top()->data_);
        }

        iterator& operator++() {
            const binary_tree* node = nodes_.top();
            nodes_.pop();
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
            if (nodes_.empty() && other.nodes_.empty()) return true;
            if (nodes_.empty() || other.nodes_.empty()) return false;
            return nodes_.top() == other.nodes_.top();
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const binary_tree*> nodes_;

        void push_left(const binary_tree* node) {
            while (node) {
                nodes_.push(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    ptr left_;
    ptr right_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) return nullptr;
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
