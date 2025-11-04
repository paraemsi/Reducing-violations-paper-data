#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>   // for std::ptrdiff_t

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

private:
    value_type data_;
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};

public:
    explicit binary_tree(const value_type &data) : data_(data) {}

    // insert a value into the correct position
    void insert(const value_type &value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }

    // getters
    const value_type &data() const { return data_; }

    std::unique_ptr<binary_tree> &left() { return left_; }
    const std::unique_ptr<binary_tree> &left() const { return left_; }

    std::unique_ptr<binary_tree> &right() { return right_; }
    const std::unique_ptr<binary_tree> &right() const { return right_; }

    // in-order iterator
    class iterator {
        std::vector<binary_tree *> stack_;

        void push_left(binary_tree *node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const value_type *;
        using reference         = const value_type &;

        iterator() = default;
        explicit iterator(binary_tree *root) { push_left(root); }

        reference operator*() const { return stack_.back()->data_; }
        pointer operator->()  const { return &stack_.back()->data_; }

        iterator &operator++() {
            auto node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator &other) const {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.back() == other.stack_.back();
        }
        bool operator!=(const iterator &other) const { return !(*this == other); }
    };

    iterator begin() { return iterator(this); }
    iterator end()   { return iterator();      }

    // const-qualified versions to allow iteration on const objects
    iterator begin() const { return iterator(const_cast<binary_tree*>(this)); }
    iterator end()   const { return iterator(); }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
