#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <stack>
#include <vector>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using pointer = std::unique_ptr<binary_tree<T>>;
    using const_pointer = const binary_tree<T>*;

    binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    const T& data() const { return data_; }
    const_pointer left() const { return left_.get(); }
    const_pointer right() const { return right_.get(); }

    void insert(const T& value) {
        if (value <= data_) {
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
        if (value == data_) {
            return true;
        } else if (value < data_) {
            return left_ ? left_->search(value) : false;
        } else {
            return right_ ? right_->search(value) : false;
        }
    }

    // In-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(const binary_tree* root) : current_(nullptr) {
            current_ = nullptr;
            const binary_tree<T>* node = root;
            while (node) {
                stack_.push(node);
                node = node->left();
            }
            advance();
        }

        reference operator*() const { return current_->data(); }
        pointer operator->() const { return &(current_->data()); }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        const binary_tree<T>* current_;
        std::stack<const binary_tree<T>*> stack_;

        void advance() {
            if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
                const binary_tree<T>* node = current_->right();
                while (node) {
                    stack_.push(node);
                    node = node->left();
                }
            } else {
                current_ = nullptr;
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

// Helper function to build a tree from a vector
template <typename T>
typename binary_tree<T>::pointer make_tree(const std::vector<T>& data) {
    if (data.empty()) return nullptr;
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
