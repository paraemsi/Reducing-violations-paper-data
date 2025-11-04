#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <cstddef>
#include <iterator>

namespace binary_search_tree {

class BinarySearchTree {
public:
    BinarySearchTree() noexcept = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const noexcept;

private:
    struct Node {
        explicit Node(std::int32_t v) noexcept : value(v), left(nullptr), right(nullptr) {}
        std::int32_t value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root_{nullptr};

    static void insert_impl(std::unique_ptr<Node>& node, std::int32_t value);
    static bool contains_impl(const std::unique_ptr<Node>& node, std::int32_t value) noexcept;
};

template<typename T>
class binary_tree {
public:
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() noexcept = default;
    explicit binary_tree(const T& value) : value_(value), has_value_(true) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&) = delete;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if (!has_value_) {
            value_ = value;
            has_value_ = true;
            return;
        }

        if ((value <= value_)) {
            if (!left_) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (!right_) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    [[nodiscard]] const T& data() const
    {
        return value_;
    }

    [[nodiscard]] tree_ptr& left() noexcept
    {
        return left_;
    }

    [[nodiscard]] const tree_ptr& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] tree_ptr& right() noexcept
    {
        return right_;
    }

    [[nodiscard]] const tree_ptr& right() const noexcept
    {
        return right_;
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() noexcept : current_(nullptr) {}

        explicit iterator(binary_tree<T>* root)
        {
            push_left(root);
            advance();
        }

        reference operator*() const
        {
            return *(current_);
        }

        pointer operator->() const
        {
            return current_;
        }

        iterator& operator++()
        {
            advance();
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            return (lhs.current_ == rhs.current_) && (lhs.stack_ == rhs.stack_);
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        void push_left(binary_tree<T>* node)
        {
            auto* current = node;
            while (current != nullptr) {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }

        void advance()
        {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }

            current_ = &(stack_.back()->value_);
            binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
        }

        std::vector<binary_tree<T>*> stack_{};
        const T* current_{nullptr};
    };

    iterator begin()
    {
        return iterator(this);
    }

    iterator end()
    {
        return iterator();
    }

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() noexcept = default;
        explicit const_iterator(const iterator& it) : impl_(it) {}

        reference operator*() const
        {
            return *impl_;
        }

        pointer operator->() const
        {
            return impl_.operator->();
        }

        const_iterator& operator++()
        {
            ++impl_;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
        {
            return (lhs.impl_ == rhs.impl_);
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        iterator impl_{};
    };

    const_iterator begin() const
    {
        return const_iterator(iterator(const_cast<binary_tree<T>*>(this)));
    }

    const_iterator end() const
    {
        return const_iterator(iterator());
    }

private:
    T value_{};
    tree_ptr left_{nullptr};
    tree_ptr right_{nullptr};
    bool has_value_{false};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
