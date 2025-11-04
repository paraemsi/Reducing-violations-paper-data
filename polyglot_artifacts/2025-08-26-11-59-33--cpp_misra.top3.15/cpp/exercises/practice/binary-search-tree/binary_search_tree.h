#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& v) : data_(v), has_value_(true) {}

    // Insert a value into the tree
    void insert(const T& value) {
        if (!has_value_) {
            data_ = value;
            has_value_ = true;
            return;
        }
        if ((value <= data_)) {
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

    // Accessors for test compatibility
    const T& data() const { return data_; }
    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }
    explicit operator bool() const { return has_value_; }

    // Iterators for in-order traversal
    class iterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree<T>* node) { traverse_left(node); }

        reference operator*() const { return stack_.back()->data_; }
        pointer operator->() const { return &(stack_.back()->data_); }

        iterator& operator++() {
            if (stack_.empty()) {
                return *this;
            }
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                traverse_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int dummy) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            // Both empty means equal (end)
            if (stack_.empty() && other.stack_.empty()) {
                return true;
            }
            // Otherwise, compare top node pointer
            if (!stack_.empty() && !other.stack_.empty()) {
                return stack_.back() == other.stack_.back();
            }
            return false;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> stack_;
        void traverse_left(const binary_tree<T>* node) {
            while ((node != nullptr) && (node->has_value_)) {
                stack_.push_back(node);
                node = node->left_ ? node->left_.get() : nullptr;
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_{};
    bool has_value_ = false;
    node_ptr left_{};
    node_ptr right_{};
};

// Helper to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    auto tree = std::make_unique<binary_tree<T>>();
    for (const auto& v : values) {
        tree->insert(v);
    }
    return tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
