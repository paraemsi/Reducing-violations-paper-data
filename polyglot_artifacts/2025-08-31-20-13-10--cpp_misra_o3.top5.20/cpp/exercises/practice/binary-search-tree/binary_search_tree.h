#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t value_in) : data(value_in) {}

        std::int32_t data;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    std::unique_ptr<Node> root_{nullptr};

    void insertNode(std::unique_ptr<Node>& node, std::int32_t value);
    [[nodiscard]] bool containsNode(const std::unique_ptr<Node>& node, std::int32_t value) const;
};

template <typename T>
class binary_tree
{
public:
    explicit binary_tree(const T& value_in) : data_{value_in} {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if ((value <= data_))
        {
            if (left_ != nullptr)
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
            if (right_ != nullptr)
            {
                right_->insert(value);
            }
            else
            {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const noexcept
    {
        return right_;
    }

    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        if ((value == data_))
        {
            return true;
        }
        if ((value < data_))
        {
            return (left_ != nullptr) ? left_->contains(value) : false;
        }
        return (right_ != nullptr) ? right_->contains(value) : false;
    }

    class const_iterator
    {
    public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using iterator_category = std::input_iterator_tag;

        const_iterator() = default;

        explicit const_iterator(const binary_tree* root)
        {
            push_left(root);
            advance();
        }

        reference operator*() const
        {
            return current_->data_;
        }

        pointer operator->() const
        {
            return &(current_->data_);
        }

        const_iterator& operator++()
        {
            advance();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            advance();
            return tmp;
        }

        [[nodiscard]] bool operator==(const const_iterator& other) const noexcept
        {
            return current_ == other.current_;
        }

        [[nodiscard]] bool operator!=(const const_iterator& other) const noexcept
        {
            return !(*this == other);
        }

    private:
        const binary_tree* current_{nullptr};
        std::vector<const binary_tree*> stack_;

        void push_left(const binary_tree* node)
        {
            const binary_tree* walker = node;
            while (walker != nullptr)
            {
                stack_.push_back(walker);
                walker = walker->left_.get();
            }
        }

        void advance()
        {
            if (stack_.empty())
            {
                current_ = nullptr;
                return;
            }

            const binary_tree* node = stack_.back();
            stack_.pop_back();
            current_ = node;

            if (node->right_ != nullptr)
            {
                push_left(node->right_.get());
            }
        }
    };

    [[nodiscard]] const_iterator begin() const
    {
        return const_iterator(this);
    }

    [[nodiscard]] const_iterator end() const
    {
        return const_iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
