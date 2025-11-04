#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using pointer = binary_tree<T>*;
    using const_pointer = const binary_tree<T>*;

    binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    // Recursively build a tree from a vector
    template <typename InputIt>
    binary_tree(InputIt first, InputIt last) : left_(nullptr), right_(nullptr) {
        if (first == last) {
            throw std::invalid_argument("Cannot build tree from empty range");
        }
        data_ = *first;
        ++first;
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    ~binary_tree() = default;

    const T& data() const { return data_; }
    pointer left() { return left_.get(); }
    pointer right() { return right_.get(); }
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

    // In-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(const binary_tree<T>* root) : current_(nullptr) {
            const binary_tree<T>* node = root;
            while (node) {
                stack_.push_back(node);
                node = node->left_.get();
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
            advance();
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
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

        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) {
        return nullptr;
    }
    return std::make_unique<binary_tree<T>>(data.begin(), data.end());
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
