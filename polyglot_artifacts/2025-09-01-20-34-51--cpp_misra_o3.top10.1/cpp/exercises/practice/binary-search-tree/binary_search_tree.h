#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <initializer_list>
#include <utility>

namespace binary_search_tree {

/*
 * A simple binary search tree that stores 32-bit signed integers.
 * Provides insertion and search operations.
 */
class BinarySearchTree
{
public:
    BinarySearchTree() noexcept = default;
    BinarySearchTree(const BinarySearchTree&)            = delete;
    BinarySearchTree(BinarySearchTree&&)                 = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&)      = delete;
    ~BinarySearchTree()                                  = default;

    /*
     * Insert a value into the tree.
     */
    void insert(std::int32_t value);

    /*
     * Search for a value in the tree.
     * \return true  – value found
     *         false – value not present
     */
    [[nodiscard]] bool search(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t v) : data(v), left(nullptr), right(nullptr) {}

        std::int32_t             data;
        std::unique_ptr<Node>    left;
        std::unique_ptr<Node>    right;
    };

    std::unique_ptr<Node> root_{nullptr};

    void insert_node(std::unique_ptr<Node>& node, std::int32_t value);
    [[nodiscard]] bool search_node(const std::unique_ptr<Node>& node,
                                   std::int32_t                value) const;
};

/*
 * Generic binary search-tree node with in-order iteration.
 * Required by unit tests.
 */
template<typename T>
class binary_tree
{
public:
    explicit binary_tree(const T& value) noexcept : value_{value}, left_{nullptr}, right_{nullptr} {}

    binary_tree(const binary_tree&)            = delete;
    binary_tree(binary_tree&&)                 = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&)      = delete;
    ~binary_tree()                             = default;

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

    [[nodiscard]] bool search(const T& value) const
    {
        if ((value == value_))
        {
            return true;
        }
        if ((value < value_))
        {
            if (left_ == nullptr)
            {
                return false;
            }
            return left_->search(value);
        }
        if (right_ == nullptr)
        {
            return false;
        }
        return right_->search(value);
    }

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

    class const_iterator
    {
    public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using reference         = const T&;
        using pointer           = const T*;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() = default;

        explicit const_iterator(const binary_tree* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.back()->value_;
        }

        pointer operator->() const
        {
            return &(stack_.back()->value_);
        }

        const_iterator& operator++()
        {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            static_cast<void>(++(*this));
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
        {
            if ((lhs.stack_.empty()) && (rhs.stack_.empty()))
            {
                return true;
            }
            if (lhs.stack_.empty() || rhs.stack_.empty())
            {
                return false;
            }
            return lhs.stack_.back() == rhs.stack_.back();
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree*> stack_;

        void push_left(const binary_tree* node)
        {
            const binary_tree* current = node;
            while (current != nullptr)
            {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }
    };

    [[nodiscard]] const_iterator begin() const
    {
        return const_iterator(this);
    }

    [[nodiscard]] const_iterator end() const
    {
        return const_iterator(nullptr);
    }

private:
    T value_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

/* Helper overloads to create a tree from any iterable sequence */
template<typename InputIt, typename T = typename std::iterator_traits<InputIt>::value_type>
std::unique_ptr<binary_tree<T>> make_tree(InputIt first, InputIt last)
{
    if (first == last)
    {
        return nullptr;
    }

    auto root = std::make_unique<binary_tree<T>>(*first);
    ++first;
    for (InputIt it = first; it != last; ++it)
    {
        root->insert(*it);
    }
    return root;
}

template<typename Container>
auto make_tree(const Container& c)
    -> std::unique_ptr<binary_tree<typename Container::value_type>>
{
    return make_tree(std::begin(c), std::end(c));
}

template<typename T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> list)
{
    return make_tree(list.begin(), list.end());
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
