#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>
#include <string>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() = delete;
    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
    explicit binary_tree(T&& value) : data_(std::move(value)), left_(nullptr), right_(nullptr) {}

    // Non-copyable, non-movable tree nodes (unique ownership via unique_ptr)
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = delete;
    binary_tree& operator=(binary_tree&&) = delete;
    ~binary_tree() = default;

    // Insert value into the tree (duplicates go to the left subtree)
    void insert(const T& value)
    {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            } else {
                right_->insert(value);
            }
        }
    }

    void insert(T&& value)
    {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(std::move(value)));
            } else {
                left_->insert(std::move(value));
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(std::move(value)));
            } else {
                right_->insert(std::move(value));
            }
        }
    }

    const T& data() const noexcept { return data_; }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    // In-order constant iterator for range-based for
    class const_iterator {
    public:
        const_iterator() noexcept : current_(nullptr), stack_() {}

        explicit const_iterator(const binary_tree<T>* root) : current_(nullptr), stack_()
        {
            push_left(root);
            advance();
        }

        const T& operator*() const noexcept { return current_->data_; }

        const_iterator& operator++()
        {
            advance();
            return *this;
        }

        bool operator==(const const_iterator& other) const noexcept
        {
            return (current_ == other.current_);
        }

        bool operator!=(const const_iterator& other) const noexcept
        {
            return (current_ != other.current_);
        }

    private:
        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node)
        {
            while ((node != nullptr)) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

        void advance()
        {
            if ((stack_.empty() == false)) {
                const binary_tree<T>* node = stack_.back();
                stack_.pop_back();
                current_ = node;
                if ((node->right_ != nullptr)) {
                    push_left(node->right_.get());
                }
            } else {
                current_ = nullptr;
            }
        }
    };

    const_iterator begin() const noexcept { return const_iterator(this); }
    const_iterator end() const noexcept { return const_iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
