#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_search_tree {
public:
    explicit binary_search_tree(const T& data) : data_{data} {}

    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_search_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_search_tree<T>>(value);
            }
        }
    }

    const T& data() const { return data_; }

    const binary_search_tree<T>* left() const { return left_.get(); }
    const binary_search_tree<T>* right() const { return right_.get(); }

    std::vector<T> sorted_data() const {
        std::vector<T> result;
        in_order_traversal(this, result);
        return result;
    }

    // iterator that traverses the tree in-order so we can
    // use range-based for loops directly on the tree object
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;
        explicit iterator(const binary_search_tree* root) { push_left(root); }

        reference operator*()  const { return stack_.back()->data_; }
        pointer   operator->() const { return &(stack_.back()->data_); }

        iterator& operator++() {
            const binary_search_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& other) const {
            if (stack_.empty() && other.stack_.empty()) return true;
            if (stack_.empty() || other.stack_.empty()) return false;
            return stack_.back() == other.stack_.back();
        }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        std::vector<const binary_search_tree*> stack_;

        void push_left(const binary_search_tree* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin()             { return iterator(this); }
    iterator end()               { return iterator(); }
    iterator begin() const       { return iterator(this); }
    iterator end()   const       { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_search_tree<T>> left_{nullptr};
    std::unique_ptr<binary_search_tree<T>> right_{nullptr};

    static void in_order_traversal(const binary_search_tree<T>* node,
                                   std::vector<T>& out) {
        if (!node) return;
        in_order_traversal(node->left(), out);
        out.push_back(node->data());
        in_order_traversal(node->right(), out);
    }
};

template <typename T>
using binary_tree = binary_search_tree<T>;

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
