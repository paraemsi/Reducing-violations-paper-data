#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

// Forward declaration so dependent translation units can refer to the
// template before its full definition is seen.
template <typename T>
class binary_tree;

template <typename T>
class binary_tree
{
public:
    using value_type = T;

    explicit binary_tree(const T& value) : data_(value) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

    void insert(const T& value)
    {
        if ((value <= data_)) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
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

    class const_iterator
    {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() noexcept = default;

        explicit const_iterator(const binary_tree* root)
        {
            push_left(root);
        }

        reference operator*() const noexcept
        {
            return stack_.back()->data_;
        }

        pointer operator->() const noexcept
        {
            return &(stack_.back()->data_);
        }

        const_iterator& operator++()
        {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if (node->right_) {
                push_left(node->right_.get());
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator temp(*this);
            static_cast<void>(++(*this));
            return temp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) noexcept
        {
            if (lhs.stack_.empty() && rhs.stack_.empty()) {
                return true;
            }
            if (lhs.stack_.empty() || rhs.stack_.empty()) {
                return false;
            }
            return lhs.stack_.back() == rhs.stack_.back();
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<const binary_tree*> stack_;

        void push_left(const binary_tree* node)
        {
            const binary_tree* current = node;
            while (current != nullptr) {
                stack_.push_back(current);
                current = current->left_ ? current->left_.get() : nullptr;
            }
        }
    };

    [[nodiscard]] const_iterator begin() const
    {
        return const_iterator(this);
    }

    [[nodiscard]] const_iterator end() const noexcept
    {
        return const_iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};
};

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() noexcept;

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node {
        explicit Node(std::int32_t val) noexcept : data(val) {}

        std::int32_t data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root_{nullptr};

    static Node* insert(Node* node, std::int32_t value);
    static bool contains(const Node* node, std::int32_t value);
    static void destroy(Node* node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
