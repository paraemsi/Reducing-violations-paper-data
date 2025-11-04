#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <utility>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value)
        : data_(value), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

    void insert(const T& value) {
        if ((value <= data_)) {
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

    bool search(const T& value) const {
        if ((value == data_)) {
            return true;
        } else if ((value < data_)) {
            return left_ ? left_->search(value) : false;
        } else {
            return right_ ? right_->search(value) : false;
        }
    }

    const T& data() const { return data_; }
    const node_ptr& left() const { return left_; }
    const node_ptr& right() const { return right_; }

    // Iterator for in-order traversal
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(binary_tree<T>* root) : current_(nullptr) {
            binary_tree<T>* node = root;
            while (node != nullptr) {
                stack_.push_back(node);
                node = node->left_.get();
            }
            advance();
        }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int dummy) {
            iterator tmp = *this;
            ++(*this);
            (void)dummy;
            return tmp;
        }

        reference operator*() const {
            return current_->data_;
        }

        pointer operator->() const {
            return &(current_->data_);
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        binary_tree<T>* current_;
        std::vector<binary_tree<T>*> stack_;

        void advance() {
            if (!(stack_.empty())) {
                current_ = stack_.back();
                stack_.pop_back();
                binary_tree<T>* node = current_->right_.get();
                while (node != nullptr) {
                    stack_.push_back(node);
                    node = node->left_.get();
                }
            } else {
                current_ = nullptr;
            }
        }
    };

    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }

private:
    T data_;
    node_ptr left_;
    node_ptr right_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if (values.empty()) {
        return nullptr;
    }
    std::unique_ptr<binary_tree<T>> root(new binary_tree<T>(values[0]));
    for (std::size_t i = 1; (i < values.size()); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
