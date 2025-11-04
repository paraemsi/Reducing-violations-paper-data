#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    using value_type = T;
    using node_type = binary_tree<T>;
    using node_ptr = std::unique_ptr<node_type>;

    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}

    void insert(const T& value) {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = node_ptr(new node_type(value));
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = node_ptr(new node_type(value));
            } else {
                right_->insert(value);
            }
        }
    }

    const T& data() const noexcept { return data_; }
    const node_ptr& left() const noexcept { return left_; }
    const node_ptr& right() const noexcept { return right_; }

    class iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(node_type* root) {
            push_left_path(root);
        }

        reference operator*() const {
            return stack_.back()->data_;
        }

        pointer operator->() const {
            return &(stack_.back()->data_);
        }

        iterator& operator++() {
            node_type* node = stack_.back();
            stack_.pop_back();
            if ((node->right_.get() != nullptr)) {
                push_left_path(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            (void)++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& a, const iterator& b) {
            if ((a.stack_.empty()) && (b.stack_.empty())) {
                return true;
            }
            if ((a.stack_.empty()) || (b.stack_.empty())) {
                return false;
            }
            return (a.stack_.back() == b.stack_.back());
        }

        friend bool operator!=(const iterator& a, const iterator& b) {
            return (!(a == b));
        }

    private:
        void push_left_path(node_type* node) {
            node_type* cur = node;
            while ((cur != nullptr)) {
                stack_.push_back(cur);
                cur = cur->left_.get();
            }
        }

        std::vector<node_type*> stack_{};
    };

    class const_iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() = default;

        explicit const_iterator(const node_type* root) {
            push_left_path(root);
        }

        reference operator*() const {
            return stack_.back()->data_;
        }

        pointer operator->() const {
            return &(stack_.back()->data_);
        }

        const_iterator& operator++() {
            const node_type* node = stack_.back();
            stack_.pop_back();
            if ((node->right_.get() != nullptr)) {
                push_left_path(node->right_.get());
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            (void)++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& a, const const_iterator& b) {
            if ((a.stack_.empty()) && (b.stack_.empty())) {
                return true;
            }
            if ((a.stack_.empty()) || (b.stack_.empty())) {
                return false;
            }
            return (a.stack_.back() == b.stack_.back());
        }

        friend bool operator!=(const const_iterator& a, const const_iterator& b) {
            return (!(a == b));
        }

    private:
        void push_left_path(const node_type* node) {
            const node_type* cur = node;
            while ((cur != nullptr)) {
                stack_.push_back(cur);
                cur = cur->left_.get();
            }
        }

        std::vector<const node_type*> stack_{};
    };

    iterator begin() noexcept { return iterator(this); }
    iterator end() noexcept { return iterator(); }
    const_iterator begin() const noexcept { return const_iterator(this); }
    const_iterator end() const noexcept { return const_iterator(); }
    const_iterator cbegin() const noexcept { return const_iterator(this); }
    const_iterator cend() const noexcept { return const_iterator(); }

private:
    T data_;
    node_ptr left_;
    node_ptr right_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> values) {
    auto it = values.begin();
    if ((it == values.end())) {
        return std::unique_ptr<binary_tree<T>>{};
    }
    auto root = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(*it));
    ++it;
    for (; (it != values.end()); ++it) {
        root->insert(*it);
    }
    return root;
}

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    if ((values.empty())) {
        return std::unique_ptr<binary_tree<T>>{};
    }
    auto root = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(values[0]));
    for (std::size_t i = 1U; (i < values.size()); ++i) {
        root->insert(values[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
