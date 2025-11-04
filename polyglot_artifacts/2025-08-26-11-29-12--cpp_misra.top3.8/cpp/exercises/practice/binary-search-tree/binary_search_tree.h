#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value)
        : value_(value), left_(nullptr), right_(nullptr) {}

    const T& data() const { return value_; }

    const binary_tree<T>* left() const { return left_ ? left_.get() : nullptr; }
    const binary_tree<T>* right() const { return right_ ? right_.get() : nullptr; }

    void insert(const T& value) {
        if ((value <= value_)) {
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

    bool contains(const T& value) const {
        if ((value == value_)) {
            return true;
        } else if ((value < value_)) {
            return left_ ? left_->contains(value) : false;
        } else {
            return right_ ? right_->contains(value) : false;
        }
    }

    // In-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(const binary_tree<T>* root) : current_(nullptr) {
            stack_.clear();
            const binary_tree<T>* node = root;
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            advance();
        }

        reference operator*() const { return current_value_; }
        pointer operator->() const { return &current_value_; }

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
            return (current_ == other.current_);
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        void advance() {
            if (!stack_.empty()) {
                const binary_tree<T>* node = stack_.back();
                stack_.pop_back();
                current_value_ = node->value_;
                const binary_tree<T>* temp = node->right_.get();
                while (temp) {
                    stack_.push_back(temp);
                    temp = temp->left_.get();
                }
                current_ = node;
            } else {
                current_ = nullptr;
            }
        }

        const binary_tree<T>* current_ = nullptr;
        std::vector<const binary_tree<T>*> stack_;
        T current_value_{};
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T value_;
    node_ptr left_;
    node_ptr right_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    std::unique_ptr<binary_tree<T>> root(new binary_tree<T>(values[0]));
    for (std::size_t i = 1; i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
