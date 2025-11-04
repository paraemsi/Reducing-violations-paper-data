#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : data_(value) {}

    const T& data() const { return data_; }

    const binary_tree* left() const { return left_.get(); }
    const binary_tree* right() const { return right_.get(); }

    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_.reset(new binary_tree(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_.reset(new binary_tree(value));
            }
        }
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        explicit iterator(const binary_tree* root) { push_left(root); set_current(); }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &current_->data_; }

        iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            set_current();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const { return current_ == other.current_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
        void set_current() {
            current_ = stack_.empty() ? nullptr : stack_.back();
        }

        const binary_tree* current_ = nullptr;
        std::vector<const binary_tree*> stack_;
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
