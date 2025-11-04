#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <stack>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& value)
        : data_(value) {}

    // Construct from vector
    explicit binary_tree(const std::vector<T>& values) {
        if (!values.empty()) {
            data_ = values[0];
            for (std::size_t i = 1; i < values.size(); ++i) {
                insert(values[i]);
            }
        }
    }

    // Insert value into tree
    void insert(const T& value) {
        if (!initialized_) {
            data_ = value;
            initialized_ = true;
            return;
        }
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

    // Search for value in tree
    bool search(const T& value) const {
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return left_ ? left_->search(value) : false;
        } else {
            return right_ ? right_->search(value) : false;
        }
    }

    // Accessors for test compatibility
    const T& data() const { return data_; }
    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }

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

        reference operator*() const { return stack_.top()->data_; }
        pointer operator->() const { return &(stack_.top()->data_); }

        iterator& operator++() {
            const binary_tree<T>* node = stack_.top();
            stack_.pop();
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
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.top() == other.stack_.top();
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::stack<const binary_tree<T>*> stack_;
        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_{};
    bool initialized_ = false;
    node_ptr left_{};
    node_ptr right_{};
};

// Helper for test code: make_tree
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    return std::make_unique<binary_tree<T>>(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
