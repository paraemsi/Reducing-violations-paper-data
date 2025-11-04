#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstdint>
#include <memory>
#include <cstddef>
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
        std::int32_t data;
        std::unique_ptr<Node> left {nullptr};
        std::unique_ptr<Node> right {nullptr};

        explicit Node(std::int32_t value) : data(value) {}
    };

    std::unique_ptr<Node> root {nullptr};

    void insertNode(std::unique_ptr<Node>& current, std::int32_t value);
    [[nodiscard]] bool containsNode(const std::unique_ptr<Node>& current, std::int32_t value) const;
}; /* end of BinarySearchTree */

/* -------------------------------------------------------------------------- */
/* Generic binary_tree template                                               */
/* -------------------------------------------------------------------------- */

template<typename T>
class binary_tree
{
public:
    binary_tree() = default;
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value)
    {
        if (!has_value_)
        {
            data_ = value;
            has_value_ = true;
        }
        else
        {
            if ((value <= data_))
            {
                if (left_ == nullptr)
                {
                    left_ = std::make_unique<binary_tree<T>>();
                }
                left_->insert(value);
            }
            else
            {
                if (right_ == nullptr)
                {
                    right_ = std::make_unique<binary_tree<T>>();
                }
                right_->insert(value);
            }
        }
    }

    [[nodiscard]] bool contains(const T& value) const
    {
        if (!has_value_)
        {
            return false;
        }

        if ((value == data_))
        {
            return true;
        }

        if ((value < data_))
        {
            return (left_ != nullptr) && (left_->contains(value));
        }
        else
        {
            return (right_ != nullptr) && (right_->contains(value));
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

    class iterator
    {
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
            return stack_.back()->data_;
        }

        pointer operator->() const
        {
            return &(stack_.back()->data_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
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

        [[nodiscard]] bool operator==(const iterator& other) const noexcept
        {
            if (stack_.empty() && other.stack_.empty())
            {
                return true;
            }
            if (stack_.empty() || other.stack_.empty())
            {
                return false;
            }
            return (stack_.back() == other.stack_.back());
        }

        [[nodiscard]] bool operator!=(const iterator& other) const noexcept
        {
            return !(*this == other);
        }

    private:
        void pushLeft(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while (current != nullptr)
            {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }

        std::vector<const binary_tree<T>*> stack_;
    };

    [[nodiscard]] iterator begin() const
    {
        return has_value_ ? iterator(this) : iterator(nullptr);
    }

    [[nodiscard]] iterator end() const
    {
        return iterator(nullptr);
    }

private:
    T data_ {};
    bool has_value_ {false};
    std::unique_ptr<binary_tree<T>> left_ {nullptr};
    std::unique_ptr<binary_tree<T>> right_ {nullptr};
};

/* convenient alias used by tests */
template<typename T>
using tree_ptr = std::unique_ptr<binary_tree<T>>;

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
