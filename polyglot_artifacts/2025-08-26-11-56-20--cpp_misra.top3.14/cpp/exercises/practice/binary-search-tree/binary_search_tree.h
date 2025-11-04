#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    binary_tree(const T& value)
        : value_(value), left_(nullptr), right_(nullptr) {}

    const T& data() const { return value_; }

    const binary_tree<T>* left() const { return left_.get(); }
    const binary_tree<T>* right() const { return right_.get(); }

    void insert(const T& value) {
        if (value <= value_) {
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
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::forward_iterator_tag;

        iterator() : current_(nullptr), current_value_() {}

        explicit iterator(const binary_tree<T>* root) : current_(nullptr), current_value_() {
            const binary_tree<T>* node = root;
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            advance();
        }

        reference operator*() const { return current_value_; }
        pointer operator->() const { return &current_value_; }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            advance();
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return (current_ == other.current_) && (stack_ == other.stack_);
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.back();
            stack_.pop_back();
            current_value_ = current_->value_;
            const binary_tree<T>* node = current_->right_.get();
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;
        T current_value_;
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

    // For test compatibility: allow unique_ptr<binary_tree<T>>
    static std::unique_ptr<binary_tree<T>> make(const std::vector<T>& values) {
        if (values.empty()) {
            return nullptr;
        }
        auto root = std::make_unique<binary_tree<T>>(values[0]);
        for (std::size_t i = 1; i < values.size(); ++i) {
            root->insert(values[i]);
        }
        return root;
    }

private:
    T value_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

template <typename T>
using tree_ptr = std::unique_ptr<binary_tree<T>>;

template <typename T>
tree_ptr<T> make_tree(const std::vector<T>& values) {
    return binary_tree<T>::make(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
