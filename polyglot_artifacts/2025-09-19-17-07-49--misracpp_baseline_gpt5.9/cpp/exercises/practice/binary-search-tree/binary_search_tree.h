#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <utility>
#include <cstddef>
#include <cstdint>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    explicit binary_tree(T value) : data_{std::move(value)} {}

    // Insert value into the tree. Duplicates go to the left subtree.
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree(value));
            }
        }
    }

    // Accessors
    const T& data() const noexcept { return data_; }
    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    // Const iterator performing in-order traversal
    class const_iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        const_iterator() = default;
        explicit const_iterator(const binary_tree<T>* root) { push_left(root); }

        reference operator*() const { return stack_.back()->data_; }
        pointer operator->() const { return &stack_.back()->data_; }

        const_iterator& operator++() {
            if (stack_.empty()) return *this;
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const noexcept {
            return stack_ == other.stack_;
        }
        bool operator!=(const const_iterator& other) const noexcept {
            return !(*this == other);
        }

    private:
        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

        std::vector<const binary_tree<T>*> stack_{};
    };

    // Begin/end for range-based for (const)
    const_iterator begin() const noexcept { return const_iterator(this); }
    const_iterator end() const noexcept { return const_iterator(); }
    // Begin/end for range-based for (non-const)
    const_iterator begin() noexcept { return const_iterator(this); }
    const_iterator end() noexcept { return const_iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
