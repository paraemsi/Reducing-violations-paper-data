#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <string>
#include <cstdint>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : data_(value) {}

    void insert(const T& value) {
        if (value <= data_) {
            if (!left_) {
                left_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            } else {
                left_->insert(value);
            }
        } else {
            if (!right_) {
                right_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            } else {
                right_->insert(value);
            }
        }
    }

    const T& data() const noexcept { return data_; }

    std::unique_ptr<binary_tree>& left() noexcept { return left_; }
    const std::unique_ptr<binary_tree>& left() const noexcept { return left_; }

    std::unique_ptr<binary_tree>& right() noexcept { return right_; }
    const std::unique_ptr<binary_tree>& right() const noexcept { return right_; }

    class iterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;

        reference operator*() const {
            return current()->data_;
        }

        pointer operator->() const {
            return &current()->data_;
        }

        iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& a, const iterator& b) {
            const binary_tree* at = a.stack_.empty() ? nullptr : a.stack_.back();
            const binary_tree* bt = b.stack_.empty() ? nullptr : b.stack_.back();
            return at == bt;
        }

        friend bool operator!=(const iterator& a, const iterator& b) {
            return !(a == b);
        }

    private:
        std::vector<const binary_tree*> stack_;

        explicit iterator(const binary_tree* root) {
            if (root) push_left(root);
        }

        void push_left(const binary_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_ ? node->left_.get() : nullptr;
            }
        }

        const binary_tree* current() const {
            return stack_.back();
        }

        friend class binary_tree;
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
