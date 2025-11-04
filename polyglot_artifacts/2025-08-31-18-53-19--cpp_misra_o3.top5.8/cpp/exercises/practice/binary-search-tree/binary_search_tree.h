#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>
#include <utility>

namespace binary_search_tree {

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    // Insert a value into the tree
    void insert(std::int32_t value);

    // Return true if the value exists in the tree
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node {
        explicit Node(std::int32_t value_in) : data(value_in) {}

        std::int32_t data;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    void insert_node(std::unique_ptr<Node>& node, std::int32_t value);
    [[nodiscard]] bool contains_node(const std::unique_ptr<Node>& node, std::int32_t value) const;

    std::unique_ptr<Node> root_{nullptr};
};

// ----------------------- generic binary_tree<T> --------------------------
template<typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value_in) : data_{value_in} {}

    binary_tree(const binary_tree&)            = delete;
    binary_tree(binary_tree&&) noexcept        = default;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

    // In-order iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return current_->data_;
        }

        pointer operator->() const
        {
            return &(current_->data_);
        }

        iterator& operator++()            // pre-increment
        {
            advance();
            return *this;
        }

        iterator operator++(int)          // NOLINT(readability-identifier-naming)
        {
            iterator temp(*this);
            advance();
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            return (lhs.current_ == rhs.current_);
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return (lhs.current_ != rhs.current_);
        }

    private:
        const binary_tree<T>* current_{nullptr};
        std::stack<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while ((current != nullptr)) {
                stack_.push(current);
                current = current->left_.get();
            }

            if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
            } else {
                current_ = nullptr;
            }
        }

        void advance()
        {
            if ((current_ == nullptr)) {
                return;
            }

            if ((current_->right_ != nullptr)) {
                push_left(current_->right_.get());
            } else if (!stack_.empty()) {
                current_ = stack_.top();
                stack_.pop();
            } else {
                current_ = nullptr;
            }
        }
    };

    [[nodiscard]] iterator begin() const
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end() const
    {
        return iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{nullptr};
    std::unique_ptr<binary_tree<T>> right_{nullptr};
};

}  // namespace binary_search_tree

#endif  // BINARY_SEARCH_TREE_H
