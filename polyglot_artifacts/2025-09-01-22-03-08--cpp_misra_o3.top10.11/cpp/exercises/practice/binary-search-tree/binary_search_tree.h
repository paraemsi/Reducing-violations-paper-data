#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstdint>
#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

// -----------------------------------------------------------------------------
// Generic binary search tree template used by the unit-tests
// -----------------------------------------------------------------------------
template<typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T &value) :
        data_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    binary_tree(const binary_tree &) = delete;
    binary_tree & operator=(const binary_tree &) = delete;
    binary_tree(binary_tree &&) noexcept = default;
    binary_tree & operator=(binary_tree &&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T &value)
    {
        if((value <= data_)) {
            if(left_ == nullptr) {
                left_ = std::make_unique<binary_tree>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if(right_ == nullptr) {
                right_ = std::make_unique<binary_tree>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    [[nodiscard]] const T & data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree> & left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree> & right() const noexcept
    {
        return right_;
    }

    // -------------------------------------------------------------------------
    // In-order iterator
    // -------------------------------------------------------------------------
    class iterator
    {
    public:
        using value_type        = T;
        using reference         = const T &;
        using pointer           = const T *;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() : current_(nullptr) {}

        explicit iterator(const binary_tree *root)
        {
            push_left(root);
            advance();
        }

        reference operator*() const
        {
            return current_->data_;
        }

        iterator & operator++()
        {
            if(current_->right_ != nullptr) {
                push_left(current_->right_.get());
            }
            advance();
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            static_cast<void>(operator++());
            return temp;
        }

        friend bool operator==(const iterator &lhs, const iterator &rhs)
        {
            return (lhs.current_ == rhs.current_);
        }

        friend bool operator!=(const iterator &lhs, const iterator &rhs)
        {
            return !(lhs == rhs);
        }

    private:
        const binary_tree * current_;
        std::stack<const binary_tree *> stack_;

        void push_left(const binary_tree *node)
        {
            const binary_tree * iter = node;
            while(iter != nullptr) {
                stack_.push(iter);
                iter = iter->left_.get();
            }
        }

        void advance()
        {
            if(stack_.empty()) {
                current_ = nullptr;
            } else {
                current_ = stack_.top();
                stack_.pop();
            }
        }
    };

    [[nodiscard]] iterator begin()
    {
        return iterator(this);
    }

    [[nodiscard]] iterator end()
    {
        return iterator();
    }

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
// -----------------------------------------------------------------------------
// End template binary_tree
// -----------------------------------------------------------------------------

class BinarySearchTree
{
private:
    struct Node
    {
        std::int32_t data;
        Node* left;
        Node* right;

        explicit Node(std::int32_t value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    static void destroy(Node* node);
    static Node* insertNode(Node* node, std::int32_t value);
    static bool containsNode(const Node* node, std::int32_t value);

public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;
    ~BinarySearchTree();

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
