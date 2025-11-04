#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <cstddef>
#include <utility>
#include <vector>

namespace binary_search_tree {

template <typename T>
struct binary_tree {
    T value_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    explicit binary_tree(const T& value) : value_(value), left_(nullptr), right_(nullptr) {}

    void insert(const T& value) {
        if (value <= value_) {
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

    const T& data() const { return value_; }
    const binary_tree<T>* left() const { return left_.get(); }
    const binary_tree<T>* right() const { return right_.get(); }

    // Iterator for in-order traversal
    struct iterator {
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root) {
            const binary_tree<T>* node = root;
            while (node) {
                stack_.push_back(node);
                node = node->left();
            }
        }

        reference operator*() const { return stack_.back()->data(); }
        pointer operator->() const { return &(stack_.back()->data()); }

        iterator& operator++() {
            if (stack_.empty()) {
                return *this;
            }
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            const binary_tree<T>* temp = node->right();
            while (temp) {
                stack_.push_back(temp);
                temp = temp->left();
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

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> stack_;
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }
};

template <typename T>
using tree_ptr = std::unique_ptr<binary_tree<T>>;

template <typename T>
tree_ptr<T> make_tree(const std::vector<T>& values) {
    tree_ptr<T> root;
    for (const auto& v : values) {
        if (!root) {
            root = std::make_unique<binary_tree<T>>(v);
        } else {
            root->insert(v);
        }
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
