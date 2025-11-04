#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>      // for std::ptrdiff_t
#include <memory>
#include <utility>
#include <vector>
#include <iterator>

namespace binary_search_tree {

class BinarySearchTree final
{
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    auto operator=(const BinarySearchTree&) -> BinarySearchTree& = delete;
    auto operator=(BinarySearchTree&&) -> BinarySearchTree& = delete;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool search(std::int32_t value) const;

private:
    struct Node final
    {
        explicit Node(std::int32_t value_in) : data(value_in), left(nullptr), right(nullptr) {}

        std::int32_t data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root_ { nullptr };

    static void insertNode(std::unique_ptr<Node>& node, std::int32_t value);
    [[nodiscard]] static bool searchNode(const std::unique_ptr<Node>& node, std::int32_t value);
};

template <typename T>
class binary_tree final
{
public:
    explicit binary_tree(const T& value_in) :
        data_(value_in),
        left_(nullptr),
        right_(nullptr)
    {
    }

    binary_tree(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = delete;
    auto operator=(const binary_tree&) -> binary_tree& = delete;
    auto operator=(binary_tree&&) -> binary_tree& = delete;
    ~binary_tree() = default;

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

    void insert(const T& value_in)
    {
        if (value_in <= data_)
        {
            if (left_ == nullptr)
            {
                left_ = std::make_unique<binary_tree>(value_in);
            }
            else
            {
                left_->insert(value_in);
            }
        }
        else
        {
            if (right_ == nullptr)
            {
                right_ = std::make_unique<binary_tree>(value_in);
            }
            else
            {
                right_->insert(value_in);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value_in) const
    {
        if (value_in == data_)
        {
            return true;
        }

        if (value_in < data_)
        {
            return ((left_ != nullptr) && (left_->contains(value_in)));
        }

        return ((right_ != nullptr) && (right_->contains(value_in)));
    }

    /* ------------------------------------------------------------------ */
    /*                     In-order traversal iterator                    */
    /* ------------------------------------------------------------------ */
    class iterator
    {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(const binary_tree* node)
        {
            pushLeft(node);
        }

        reference operator*() const
        {
            return stack_.back()->data();
        }

        pointer operator->() const
        {
            return &(stack_.back()->data());
        }

        iterator& operator++()
        {
            const binary_tree* current_node { stack_.back() };
            stack_.pop_back();
            if (current_node->right() != nullptr)
            {
                pushLeft(current_node->right().get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp { *this };
            ++(*this);
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            return lhs.stack_ == rhs.stack_;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree*> stack_;

        void pushLeft(const binary_tree* node)
        {
            const binary_tree* current_node { node };
            while (current_node != nullptr)
            {
                stack_.push_back(current_node);
                current_node = current_node->left().get();
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
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
