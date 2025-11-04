#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>   // for std::forward_iterator_tag
#include <cstddef>    // for std::ptrdiff_t

namespace binary_search_tree {

using int_type = std::uint32_t;

template<typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : value_(value) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if ((value <= value_))
        {
            if (left_ == nullptr)
            {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                left_->insert(value);
            }
        }
        else
        {
            if (right_ == nullptr)
            {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                right_->insert(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if ((value == value_))
        {
            return true;
        }
        if ((value < value_))
        {
            return (left_ != nullptr) && (left_->contains(value));
        }
        return (right_ != nullptr) && (right_->contains(value));
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return value_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

    /* in-order iterator */
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        explicit iterator(const binary_tree<T>* root)
        {
            pushLeft(root);
        }

        reference operator*() const
        {
            return stack_.top()->value_;
        }

        pointer operator->() const
        {
            return &(stack_.top()->value_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* node = stack_.top();
            stack_.pop();
            if (node->right_ != nullptr)
            {
                pushLeft(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            static_cast<void>(++(*this));
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            if (lhs.stack_.empty() && rhs.stack_.empty())
            {
                return true;
            }
            if (lhs.stack_.empty() || rhs.stack_.empty())
            {
                return false;
            }
            return lhs.stack_.top() == rhs.stack_.top();
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::stack<const binary_tree<T>*> stack_{};

        void pushLeft(const binary_tree<T>* node)
        {
            while (node != nullptr)
            {
                stack_.push(node);
                node = node->left_.get();
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
    T value_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    void insert(int_type value);
    [[nodiscard]] bool contains(int_type value) const;

private:
    struct Node {
        explicit Node(int_type val) : data(val), left(nullptr), right(nullptr) {}

        int_type data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    void insertRecursive(std::unique_ptr<Node>& node, int_type value);
    [[nodiscard]] bool containsRecursive(const std::unique_ptr<Node>& node, int_type value) const;

    std::unique_ptr<Node> root {};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
