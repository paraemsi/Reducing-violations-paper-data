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
    explicit binary_tree(const T& data) : data_(data) {}

    const T& data() const { return data_; }

    std::unique_ptr<binary_tree<T>>& left() { return left_; }
    std::unique_ptr<binary_tree<T>>& right() { return right_; }
    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_.reset(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_.reset(new binary_tree<T>(value));
            }
        }
    }

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() : current_(nullptr) {}
        explicit iterator(binary_tree<T>* root) : current_(nullptr) {
            descend_left(root);
        }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &current_->data_; }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            advance();
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_ && stack_ == other.stack_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<binary_tree<T>*> stack_;
        binary_tree<T>* current_;

        void descend_left(binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            advance();
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.back();
            stack_.pop_back();

            auto node = current_->right_.get();
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    // Const iterator for in-order traversal
    class const_iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : current_(nullptr) {}
        explicit const_iterator(const binary_tree<T>* root) : current_(nullptr) {
            descend_left(root);
        }

        reference operator*() const { return current_->data_; }
        pointer operator->() const { return &current_->data_; }

        const_iterator& operator++() {
            advance();
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            advance();
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return current_ == other.current_ && stack_ == other.stack_;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree<T>*> stack_;
        const binary_tree<T>* current_;

        void descend_left(const binary_tree<T>* node) {
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            advance();
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            current_ = stack_.back();
            stack_.pop_back();

            auto node = current_->right_.get();
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }
    };

    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }
    const_iterator begin() const { return const_iterator(this); }
    const_iterator end() const { return const_iterator(); }

    // Grant iterators access to private members
    friend class iterator;
    friend class const_iterator;

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
