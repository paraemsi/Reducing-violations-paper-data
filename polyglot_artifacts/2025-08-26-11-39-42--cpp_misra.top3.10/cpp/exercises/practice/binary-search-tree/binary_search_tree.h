#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

// Forward declaration for template
template <typename T>
class binary_tree;

// Node for the non-template BinarySearchTree
using value_type = std::int32_t;

struct Node
{
    value_type data;
    Node* left;
    Node* right;

    explicit Node(value_type val);
    ~Node() = default;
};

// Non-template BinarySearchTree (legacy, for backward compatibility)
class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(value_type value);
    bool search(value_type value) const;

private:
    Node* root;

    void insert(Node*& node, value_type value);
    bool search(const Node* node, value_type value) const;
    void destroy(Node* node);
};

// Modern template-based binary_tree for generic tests
template <typename T>
class binary_tree
{
public:
    struct node
    {
        T data;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        explicit node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    using node_type = node;
    using value_type = T;

    binary_tree() : root_(nullptr) {}

    explicit binary_tree(const std::vector<T>& values) : root_(nullptr)
    {
        for (const auto& v : values)
        {
            insert(v);
        }
    }

    void insert(const T& value)
    {
        insert_impl(root_, value);
    }

    const T& data() const
    {
        return root_->data;
    }

    // Return a pointer to a new binary_tree representing the left subtree, or nullptr if none.
    const binary_tree* left() const
    {
        if (root_ && root_->left)
        {
            return new binary_tree(root_->left.get());
        }
        return nullptr;
    }

    // Return a pointer to a new binary_tree representing the right subtree, or nullptr if none.
    const binary_tree* right() const
    {
        if (root_ && root_->right)
        {
            return new binary_tree(root_->right.get());
        }
        return nullptr;
    }

    // In-order iterator support
    struct iterator
    {
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(const node* root)
        {
            // In-order traversal: push all left children
            current_ = nullptr;
            const node* n = root;
            while (n)
            {
                stack_.push_back(n);
                n = n->left.get();
            }
            advance();
        }

        reference operator*() const { return current_->data; }
        pointer operator->() const { return &(current_->data); }

        iterator& operator++()
        {
            advance();
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            return current_ == other.current_;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

    private:
        const node* current_;
        std::vector<const node*> stack_;

        void advance()
        {
            if (!stack_.empty())
            {
                current_ = stack_.back();
                stack_.pop_back();
                const node* n = current_->right.get();
                while (n)
                {
                    stack_.push_back(n);
                    n = n->left.get();
                }
            }
            else
            {
                current_ = nullptr;
            }
        }
    };

    iterator begin() const
    {
        return iterator(root_.get());
    }

    iterator end() const
    {
        return iterator();
    }

private:
    std::unique_ptr<node> root_;

    // Helper for copy construction from a subtree
    explicit binary_tree(const node* n)
        : root_(nullptr)
    {
        if (n)
        {
            root_ = std::make_unique<node>(n->data);
            if (n->left)
                root_->left = std::make_unique<node>(*n->left);
            if (n->right)
                root_->right = std::make_unique<node>(*n->right);
        }
    }

    void insert_impl(std::unique_ptr<node>& n, const T& value)
    {
        if (!n)
        {
            n = std::make_unique<node>(value);
        }
        else if (value <= n->data)
        {
            insert_impl(n->left, value);
        }
        else
        {
            insert_impl(n->right, value);
        }
    }
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values)
{
    return std::make_unique<binary_tree<T>>(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
