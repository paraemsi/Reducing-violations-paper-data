#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <stack>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree;

class BinarySearchTree
{
public:
    using ValueType = std::int32_t;

    BinarySearchTree() = default;
    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;

    void insert(ValueType value);
    bool search(ValueType value) const;

private:
    struct Node
    {
        ValueType data;
        Node* left;
        Node* right;
    };

    Node* root_{nullptr};

    static Node* insertNode(Node* node, ValueType value);
    static bool searchNode(const Node* node, ValueType value);
    static void destroy(Node* node);
};

template<typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_(value) {}

    void insert(const T& value)
    {
        if ((value <= value_))
        {
            if (left_ == nullptr)
            {
                left_ = std::make_unique<binary_tree>(value);
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
                right_ = std::make_unique<binary_tree>(value);
            }
            else
            {
                right_->insert(value);
            }
        }
    }

    const T& data() const noexcept
    {
        return value_;
    }

    const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return left_;
    }

    const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return right_;
    }

private:
    T value_;
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};

public: // iterator
    class const_iterator
    {
    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() = default;

        explicit const_iterator(const binary_tree* root)
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

        const_iterator& operator++()
        {
            const binary_tree* const node = stack_.top();
            stack_.pop();
            pushLeft(node->right_.get());
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            (void)operator++();
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
        {
            if ((lhs.stack_.empty()) && (rhs.stack_.empty()))
            {
                return true;
            }
            if ((lhs.stack_.empty()) || (rhs.stack_.empty()))
            {
                return false;
            }
            return lhs.stack_.top() == rhs.stack_.top();
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::stack<const binary_tree*> stack_;

        void pushLeft(const binary_tree* node)
        {
            const binary_tree* current = node;
            while (current != nullptr)
            {
                stack_.push(current);
                current = current->left_.get();
            }
        }
    };

    const_iterator begin() const
    {
        return const_iterator(this);
    }

    const_iterator end() const
    {
        return const_iterator();
    }
};

} // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
