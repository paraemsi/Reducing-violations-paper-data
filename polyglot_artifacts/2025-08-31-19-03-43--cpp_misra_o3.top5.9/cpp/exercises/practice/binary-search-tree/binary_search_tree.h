#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstdint>
#include <cstddef>

namespace binary_search_tree {

struct Node
{
    explicit Node(std::int32_t value) : data(value), left(nullptr), right(nullptr) {}

    std::int32_t               data;
    std::unique_ptr<Node>      left;
    std::unique_ptr<Node>      right;
};

class BinarySearchTree
{
public:
    BinarySearchTree() = default;

    void insert(std::int32_t value);
    bool contains(std::int32_t value) const;

private:
    std::unique_ptr<Node> root_{nullptr};

    void insert(std::unique_ptr<Node>& node, std::int32_t value);
    bool contains(const std::unique_ptr<Node>& node, std::int32_t value) const;
};

template<typename T>
class binary_tree
{
public:
    explicit binary_tree(const T& value) : data_{value}, left_{nullptr}, right_{nullptr} {}

    void insert(const T& value)
    {
        insert_node(*this, value);
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

    /* In-order forward iterator ********************************************/
    class iterator
    {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() noexcept : current_{nullptr} {}

        /* constructor that positions at the smallest element */
        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
            advance();
        }

        reference operator*() const
        {
            return current_->data_;
        }

        iterator& operator++()
        {
            advance();
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp{*this};   /* mandatory int dummy kept */
            advance();
            return temp;
        }

        [[nodiscard]] bool operator==(const iterator& other) const noexcept
        {
            return ((current_ == other.current_) && (stack_ == other.stack_));
        }

        [[nodiscard]] bool operator!=(const iterator& other) const noexcept
        {
            return !((*this) == other);
        }

    private:

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* n{node};
            while (n != nullptr)
            {
                stack_.push_back(n);
                n = n->left_.get();
            }
        }

        void advance()
        {
            if (stack_.empty())
            {
                current_ = nullptr;
                return;
            }

            const binary_tree<T>* node{stack_.back()};
            stack_.pop_back();
            current_ = node;

            if (node->right_ != nullptr)
            {
                push_left(node->right_.get());
            }
        }

        const binary_tree<T>*              current_{nullptr};
        std::vector<const binary_tree<T>*> stack_;

        friend class binary_tree<T>;
    };
    /*************************************************************************/

    [[nodiscard]] iterator begin() const
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end() const noexcept
    {
        return iterator();
    }

private:
    static void insert_node(binary_tree<T>& node, const T& value)
    {
        if ((value <= node.data_))
        {
            if (node.left_ == nullptr)
            {
                node.left_ = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                insert_node(*node.left_, value);
            }
        }
        else
        {
            if (node.right_ == nullptr)
            {
                node.right_ = std::make_unique<binary_tree<T>>(value);
            }
            else
            {
                insert_node(*node.right_, value);
            }
        }
    }

    T                                   data_;
    std::unique_ptr<binary_tree<T>>     left_;
    std::unique_ptr<binary_tree<T>>     right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
