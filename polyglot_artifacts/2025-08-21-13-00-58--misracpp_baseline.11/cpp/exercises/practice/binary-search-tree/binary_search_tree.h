#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree(const T& value) : data_(value) {}

    const T& data() const { return data_; }

    const ptr& left() const { return left_; }
    const ptr& right() const { return right_; }

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

    // In-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(const binary_tree* root) {
            current_ = root;
            while (current_) {
                stack_.push_back(current_);
                current_ = current_->left_.get();
            }
            advance();
        }

        reference operator*() { return current_value_; }
        pointer operator->() { return &current_value_; }

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
        const binary_tree* current_ = nullptr;
        std::vector<const binary_tree<T>*> stack_;
        T current_value_{};

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            current_value_ = node->data_;
            if (node->right_) {
                const binary_tree* n = node->right_.get();
                while (n) {
                    stack_.push_back(n);
                    n = n->left_.get();
                }
            }
            current_ = node;
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    ptr left_ = nullptr;
    ptr right_ = nullptr;
};

template <typename T>
typename binary_tree<T>::ptr make_tree(const std::vector<T>& values) {
    if (values.empty()) return nullptr;
    auto root = std::make_unique<binary_tree<T>>(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
