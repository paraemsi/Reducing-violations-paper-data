#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_(value) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(binary_tree&&) = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if (value <= value_)
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

    [[nodiscard]] const T& data() const
    {
        return value_;
    }

    [[nodiscard]] std::unique_ptr<binary_tree>& left()
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const
    {
        return left_;
    }

    [[nodiscard]] std::unique_ptr<binary_tree>& right()
    {
        return right_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const
    {
        return right_;
    }

    class iterator
    {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(const binary_tree* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return node_stack_.back()->value_;
        }

        pointer operator->() const
        {
            return &(node_stack_.back()->value_);
        }

        iterator& operator++()
        {
            const binary_tree* node = node_stack_.back();
            node_stack_.pop_back();
            if (node->right_ != nullptr)
            {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator old(*this);
            static_cast<void>(++(*this));
            return old;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            if (lhs.node_stack_.empty() && rhs.node_stack_.empty())
            {
                return true;
            }
            if ((!lhs.node_stack_.empty()) && (!rhs.node_stack_.empty()))
            {
                return lhs.node_stack_.back() == rhs.node_stack_.back();
            }
            return false;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        void push_left(const binary_tree* node)
        {
            auto current = node;
            while (current != nullptr)
            {
                node_stack_.push_back(current);
                current = current->left_.get();
            }
        }

        std::vector<const binary_tree*> node_stack_{};
    };

    // public iteration helpers
    [[nodiscard]] iterator begin()
    {
        return iterator(this);
    }

    [[nodiscard]] iterator begin() const
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end()
    {
        return iterator();
    }

    [[nodiscard]] iterator end() const
    {
        return iterator();
    }

    // duplicate end() removed; single set of overloads kept later

private:
    T value_;
    std::unique_ptr<binary_tree> left_{};
    std::unique_ptr<binary_tree> right_{};
};

class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&& other) = default;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&& other) = default;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t val) : data(val) {}
        std::int32_t data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    void insert_impl(std::unique_ptr<Node>& subtree, std::int32_t value);
    [[nodiscard]] bool contains_impl(const std::unique_ptr<Node>& subtree, std::int32_t value) const;

    std::unique_ptr<Node> root{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
