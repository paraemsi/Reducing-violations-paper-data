#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    using value_type = std::int32_t;

    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = default;
    BinarySearchTree& operator=(BinarySearchTree&&) = default;
    ~BinarySearchTree() = default;

    void insert(value_type value);
    [[nodiscard]] bool contains(value_type value) const;

private:
    struct Node
    {
        explicit Node(value_type v);

        value_type data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    void insertRec(std::unique_ptr<Node>& current, value_type value);
    [[nodiscard]] bool containsRec(const std::unique_ptr<Node>& current, value_type value) const;

    std::unique_ptr<Node> root_{nullptr};
};

/* -------------------------------------------------------------------------- */
/* New generic binary_tree implementation expected by the unit–tests          */
/* -------------------------------------------------------------------------- */
template<typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value) :
        value_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    void insert(const T& value)
    {
        if((value <= value_))
        {
            if(left_ != nullptr)
            {
                left_->insert(value);
            }
            else
            {
                left_ = std::make_unique<binary_tree>(value);
            }
        }
        else
        {
            if(right_ != nullptr)
            {
                right_->insert(value);
            }
            else
            {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if((value == value_))
        {
            return true;
        }
        if((value < value_))
        {
            return (left_ != nullptr) && (left_->contains(value));
        }
        return (right_ != nullptr) && (right_->contains(value));
    }

    /* accessors required by the tests */
    [[nodiscard]] const T& data() const noexcept
    {
        return value_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return right_;
    }

    /* ------------------------------------------------------------------ */
    /* iterator providing in-order traversal so that *tree is range-based  */
    /* ------------------------------------------------------------------ */
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree* root)
        {
            init(root);
        }

        reference operator*() const
        {
            return *current_;
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
            iterator temp(*this);   /* mandatory dummy int parameter kept */
            ++(*this);
            return temp;
        }

        [[nodiscard]] bool operator==(const iterator& other) const noexcept
        {
            return current_ == other.current_;
        }

        [[nodiscard]] bool operator!=(const iterator& other) const noexcept
        {
            return !(*this == other);
        }

    private:
        using node_ptr = const binary_tree*;

        void init(node_ptr root)
        {
            node_ptr node = root;
            while(node != nullptr)
            {
                stack_.push(node);
                node = node->left_.get();
            }
            advance();
        }

        void advance()
        {
            if(stack_.empty())
            {
                current_ = nullptr;
                return;
            }

            node_ptr node = stack_.top();
            stack_.pop();
            current_ = &(node->value_);

            node_ptr right_child = node->right_.get();
            while(right_child != nullptr)
            {
                stack_.push(right_child);
                right_child = right_child->left_.get();
            }
        }

        std::stack<node_ptr> stack_{};
        pointer current_{nullptr};
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
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
