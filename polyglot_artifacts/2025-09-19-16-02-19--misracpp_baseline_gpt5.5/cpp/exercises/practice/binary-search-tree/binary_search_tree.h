#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <utility>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    explicit binary_tree(const T& value) : data_(value) {}
    explicit binary_tree(T&& value) : data_(std::move(value)) {}

    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            }
        }
    }

    const T& data() const { return data_; }

    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr) {}
        explicit iterator(const binary_tree<T>* root) : current_(nullptr) {
            push_left(root);
            advance();
        }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &current_->data_; }

        iterator& operator++() {
            advance();
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            advance();
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_ && stack_ == other.stack_;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> stack_;
        const binary_tree<T>* current_;

        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            current_ = node;
            if (node->right_) {
                push_left(node->right_.get());
            }
        }

        
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
