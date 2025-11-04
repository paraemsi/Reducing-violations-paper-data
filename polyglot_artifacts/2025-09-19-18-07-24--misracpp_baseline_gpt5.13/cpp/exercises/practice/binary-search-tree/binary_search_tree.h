#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iterator>
#include <memory>
#include <vector>

namespace binary_search_tree {

// A templated Binary Search Tree node type.
// Duplicates are inserted into the left subtree.
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    // Accessors
    const T& data() const noexcept { return data_; }
    const tree_ptr& left() const noexcept { return left_; }
    const tree_ptr& right() const noexcept { return right_; }

    // Insert a value into the tree. Duplicates go left.
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = tree_ptr(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = tree_ptr(new binary_tree<T>(value));
            }
        }
    }

    // Forward iterator over the tree in sorted (in-order) sequence.
    class iterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = const T&;
        using pointer = const T*;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        reference operator*() const { return stack_.back()->data_; }
        pointer operator->() const { return &stack_.back()->data_; }

        iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.back() == other.stack_.back();
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        friend class binary_tree<T>;
        explicit iterator(const binary_tree<T>* root) { push_left(root); }

        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

        std::vector<const binary_tree<T>*> stack_;
    };

    // Begin/end produce iterators over the tree in-order.
    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    tree_ptr left_;
    tree_ptr right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
