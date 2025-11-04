#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <iterator>
#include <memory>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    void insert(const T& value) {
        if ((value <= data_)) {
            if ((left_ != nullptr)) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if ((right_ != nullptr)) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    const T& data() const noexcept {
        return data_;
    }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept {
        return left_;
    }

    const std::unique_ptr<binary_tree<T>>& right() const noexcept {
        return right_;
    }

    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() noexcept : current_(nullptr), stack_() {}

        explicit iterator(const binary_tree<T>* root) : current_(nullptr), stack_() {
            push_left(root);
            advance();
        }

        reference operator*() const {
            return current_->data_;
        }

        pointer operator->() const {
            return &(current_->data_);
        }

        iterator& operator++() {
            advance();
            return *this;
        }

        bool operator==(const iterator& other) const noexcept {
            return (current_ == other.current_);
        }

        bool operator!=(const iterator& other) const noexcept {
            return (current_ != other.current_);
        }

    private:
        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* n = node;
            while ((n != nullptr)) {
                stack_.push_back(n);
                n = n->left_.get();
            }
        }

        void advance() {
            if ((stack_.empty())) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
                stack_.pop_back();
                if ((current_->right_ != nullptr)) {
                    push_left(current_->right_.get());
                }
            }
        }
    };

    iterator begin() const noexcept {
        return iterator(this);
    }

    iterator end() const noexcept {
        return iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
