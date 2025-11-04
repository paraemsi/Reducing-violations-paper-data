#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <stack>
#include <iterator>
#include <vector>
#include <initializer_list>

namespace binary_search_tree {

class BinarySearchTree
{
public:
    BinarySearchTree() noexcept;
    ~BinarySearchTree();

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;

private:
    struct Node
    {
        explicit Node(std::int32_t v) noexcept : value(v), left(nullptr), right(nullptr) {}

        std::int32_t value;
        Node* left;
        Node* right;
    };

    Node* root_;

    static void destroy(Node* node) noexcept;
    static void insert(Node*& node, std::int32_t value);
    static bool contains(const Node* node, std::int32_t value);
};

/*
 * Generic binary search tree used by the unit-tests.
 */
template<typename T>
class binary_tree
{
public:
    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}

    void insert(const T& value)
    {
        if (value <= data_) {
            if (left_ == nullptr) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (right_ == nullptr) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
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
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() = default;

        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.top()->data_;
        }

        pointer operator->() const
        {
            return &(stack_.top()->data_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* current = stack_.top();
            stack_.pop();
            push_left(current->right_.get());
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);   /* NOLINT(cppcoreguidelines-pro-type-member-init) */
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            if ((lhs.stack_.empty()) && (rhs.stack_.empty())) {
                return true;
            }
            if ((!lhs.stack_.empty()) && (!rhs.stack_.empty())) {
                return lhs.stack_.top() == rhs.stack_.top();
            }
            return false;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::stack<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while (current != nullptr) {
                stack_.push(current);
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
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

/*
 * Helper factory that the unit-tests expect.
 */
template<typename T>
[[nodiscard]] inline std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values)
{
    if (values.empty()) {
        return nullptr;
    }

    auto root = std::make_unique<binary_tree<T>>(values.front());
    for (std::size_t i = static_cast<std::size_t>(1); i < values.size(); ++i) {
        root->insert(values[i]);
    }
    return root;
}

template<typename T>
[[nodiscard]] inline std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> values)
{
    return make_tree(std::vector<T>(values));
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
