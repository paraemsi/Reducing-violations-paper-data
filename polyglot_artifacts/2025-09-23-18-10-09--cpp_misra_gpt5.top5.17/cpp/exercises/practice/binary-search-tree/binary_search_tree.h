#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <iterator>
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    void insert(const T& value) {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_.reset(new binary_tree<T>(value));
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_.reset(new binary_tree<T>(value));
            } else {
                right_->insert(value);
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

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::int64_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : current_(nullptr) {}

        reference operator*() const {
            return current_->data_;
        }

        pointer operator->() const {
            return &(current_->data_);
        }

        const_iterator& operator++() {
            advance();
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            advance();
            return tmp;
        }

        friend bool operator==(const const_iterator& a, const const_iterator& b) {
            return (a.current_ == b.current_);
        }

        friend bool operator!=(const const_iterator& a, const const_iterator& b) {
            return (a.current_ != b.current_);
        }

    private:
        friend class binary_tree<T>;

        explicit const_iterator(const binary_tree<T>* root) : current_(nullptr) {
            push_left(root);
            if ((stack_.empty())) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
            }
        }

        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* cursor = node;
            while ((cursor != nullptr)) {
                stack_.push_back(cursor);
                cursor = cursor->left_.get();
            }
        }

        void advance() {
            if ((current_ == nullptr)) {
                return;
            }

            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();

            if ((node->right_ != nullptr)) {
                push_left(node->right_.get());
            }

            if ((stack_.empty())) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
            }
        }

        std::vector<const binary_tree<T>*> stack_{};
        const binary_tree<T>* current_;
    };

    const_iterator begin() noexcept {
        return const_iterator(this);
    }

    const_iterator begin() const noexcept {
        return const_iterator(this);
    }

    const_iterator end() noexcept {
        return const_iterator();
    }

    const_iterator end() const noexcept {
        return const_iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
