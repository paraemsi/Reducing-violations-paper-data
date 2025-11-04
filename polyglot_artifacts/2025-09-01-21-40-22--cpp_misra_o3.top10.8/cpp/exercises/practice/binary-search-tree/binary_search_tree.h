#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>

namespace binary_search_tree
{

/*
 * Generic binary search tree node that owns its children via std::unique_ptr.
 *  – supports insertion of duplicate values (duplicates go to the left side)
 *  – provides left(), right(), data() accessors used by the tests
 *  – exposes in-order iterators so the whole tree is range-iterable
 */
template <typename T>
class binary_tree
{
public:
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value_in) : data_(value_in) {}

    void insert(const T& value)
    {
        if ((value <= data_))
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

    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const node_ptr& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const node_ptr& right() const noexcept
    {
        return right_;
    }

    /* ---------------- iterator ---------------- */

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.back()->data_;
        }

        pointer operator->() const
        {
            return &(stack_.back()->data_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* current = stack_.back();
            stack_.pop_back();
            push_left(current->right_.get());
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);          /* mandatory int dummy kept as required */
            return tmp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            if ((lhs.stack_.empty()) && (rhs.stack_.empty()))
            {
                return true;
            }
            if ((lhs.stack_.empty()) || (rhs.stack_.empty()))
            {
                return false;
            }
            return lhs.stack_.back() == rhs.stack_.back();
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree<T>*> stack_{};

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while (current != nullptr)
            {
                stack_.push_back(current);
                current = current->left_.get();
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
    T           data_;
    node_ptr    left_{nullptr};
    node_ptr    right_{nullptr};
};

class BinarySearchTree
{
public:
    BinarySearchTree() noexcept;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const noexcept;

private:
    struct Node
    {
        std::int32_t data{};
        Node* left{nullptr};
        Node* right{nullptr};

        explicit Node(std::int32_t value_in) noexcept : data(value_in), left(nullptr), right(nullptr) {}
    };

    Node* root_{nullptr};

    static void destroy_subtree(Node* node) noexcept;
    static Node* insert(Node* node, std::int32_t value);
    static bool contains(const Node* node, std::int32_t value) noexcept;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
