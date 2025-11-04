#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value)
        : data_(value), left_(), right_() {}

    const T& data() const { return data_; }

    const tree_ptr& left() const { return left_; }
    const tree_ptr& right() const { return right_; }

    void insert(const T& value) {
        if ((value <= data_)) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    bool search(const T& value) const {
        if ((value == data_)) {
            return true;
        } else if ((value < data_)) {
            return (left_ ? left_->search(value) : false);
        } else {
            return (right_ ? right_->search(value) : false);
        }
    }

    // In-order iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() : current_(nullptr) {}

        explicit iterator(const binary_tree<T>* root) : current_(nullptr) {
            if (root != nullptr) {
                const binary_tree<T>* node = root;
                while (node) {
                    stack_.push_back(node);
                    node = node->left_.get();
                }
                advance();
            }
        }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &(current_->data_); }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int dummy) {
            (void)dummy;
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return (current_ == other.current_);
        }

        bool operator!=(const iterator& other) const {
            return (current_ != other.current_);
        }

    private:
        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.back();
            stack_.pop_back();
            const binary_tree<T>* node = current_->right_.get();
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    tree_ptr left_;
    tree_ptr right_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (std::size_t i = 1; (i < values.size()); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
