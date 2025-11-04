#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <string>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    class iterator;
    friend class iterator;

    explicit binary_tree(const T& value)
        : value_(value), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

    void insert(const T& value) {
        if ((value <= value_)) {
            if ((left_ == nullptr)) {
                left_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            } else {
                right_->insert(value);
            }
        }
    }

    bool contains(const T& value) const noexcept {
        if ((value == value_)) {
            return true;
        }

        if ((value < value_)) {
            if ((left_ == nullptr)) {
                return false;
            } else {
                return left_->contains(value);
            }
        } else {
            if ((right_ == nullptr)) {
                return false;
            } else {
                return right_->contains(value);
            }
        }
    }

    const T& data() const noexcept {
        return value_;
    }

    const std::unique_ptr<binary_tree>& left() const noexcept {
        return left_;
    }

    const std::unique_ptr<binary_tree>& right() const noexcept {
        return right_;
    }

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() noexcept : current_(nullptr), stack_() {}

        explicit iterator(const binary_tree* root) : current_(nullptr), stack_() {
            push_left(root);
            set_current();
        }

        reference operator*() const {
            return stack_.back()->value_;
        }

        pointer operator->() const {
            return &(stack_.back()->value_);
        }

        iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if ((node->right_ != nullptr)) {
                push_left(node->right_.get());
            }
            set_current();
            return *this;
        }

        iterator operator++(int) {
            iterator prev = *this;
            ++(*this);
            return prev;
        }

        bool operator==(const iterator& other) const noexcept {
            if ((current_ == nullptr) && (other.current_ == nullptr)) {
                return true;
            }
            if ((current_ == nullptr) || (other.current_ == nullptr)) {
                return false;
            }
            return (current_ == other.current_);
        }

        bool operator!=(const iterator& other) const noexcept {
            return !(operator==(other));
        }

    private:
        const binary_tree* current_;
        std::vector<const binary_tree*> stack_;

        void push_left(const binary_tree* node) {
            const binary_tree* it = node;
            while ((it != nullptr)) {
                stack_.push_back(it);
                it = it->left_.get();
            }
        }

        void set_current() noexcept {
            if ((stack_.empty())) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
            }
        }
    };

    iterator begin() const noexcept {
        return iterator(this);
    }

    iterator end() const noexcept {
        return iterator();
    }

private:
    T value_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
