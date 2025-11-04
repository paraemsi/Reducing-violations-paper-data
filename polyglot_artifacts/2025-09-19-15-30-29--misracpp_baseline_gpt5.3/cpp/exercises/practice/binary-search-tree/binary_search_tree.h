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
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) { push_left(root); }

        reference operator*() const { return stack_.back()->data(); }
        pointer operator->() const { return &stack_.back()->data(); }

        iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if (node->right()) {
                push_left(node->right().get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.back() == other.stack_.back();
        }

        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left().get();
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
