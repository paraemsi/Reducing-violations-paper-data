#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <cstddef>
#include <iterator>
#include <string>

namespace binary_search_tree {

//-----------------------------------------------------------------------------
// A minimal binary-search-tree node that satisfies the unit-test expectations.
// It is a single-node structure (each node *is* a tree) and therefore the
// entire implementation can live in this header (templates must be visible
// to translation units that use them).
//-----------------------------------------------------------------------------
template <typename T>
class binary_tree {
public:
    //----- rule-of-five ------------------------------------------------------
    explicit binary_tree(const T& value) : data_(value) {}
    binary_tree(const binary_tree&)            = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept        = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    //----- modifiers ---------------------------------------------------------
    void insert(const T& value)
    {
        if ((value <= data_)) {
            insert_child(left_, value);
        } else {
            insert_child(right_, value);
        }
    }

    //----- queries -----------------------------------------------------------
    [[nodiscard]] bool contains(const T& value) const
    {
        if ((value == data_)) {
            return true;
        }

        if ((value < data_)) {
            return contains_child(left_, value);
        }

        return contains_child(right_, value);
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

    //----- iterator for range-based for (in-order traversal) -----------------
    class iterator {
    public:
        using value_type        = T;
        using reference         = const T&;
        using pointer           = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        explicit iterator(const binary_tree* root)
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

        iterator& operator++()            // prefix
        {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        iterator operator++(int)          // postfix (MISRA: dummy int param)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }

        [[nodiscard]] bool operator==(const iterator& other) const
        {
            if (stack_.empty() && other.stack_.empty()) {
                return true;
            }

            if (stack_.empty() || other.stack_.empty()) {
                return false;
            }

            return stack_.back() == other.stack_.back();
        }

        [[nodiscard]] bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

    private:
        std::vector<const binary_tree*> stack_{};

        void push_left(const binary_tree* node)
        {
            const binary_tree* current = node;
            while (current != nullptr) {
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
    using node_ptr = std::unique_ptr<binary_tree>;

    T         data_;
    node_ptr  left_{};
    node_ptr  right_{};

    static void insert_child(node_ptr& child, const T& value)
    {
        if (!child) {
            child = std::make_unique<binary_tree>(value);
        } else {
            child->insert(value);
        }
    }

    static bool contains_child(const node_ptr& child, const T& value)
    {
        return child ? child->contains(value) : false;
    }
};

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = default;
    BinarySearchTree& operator=(BinarySearchTree&&) = default;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node {
        explicit Node(std::int32_t v) : data(v) {}
        std::int32_t data;
        std::unique_ptr<Node> left{};
        std::unique_ptr<Node> right{};
    };

    void insert(std::unique_ptr<Node>& current, std::int32_t value);
    [[nodiscard]] bool contains(const std::unique_ptr<Node>& current, std::int32_t value) const;

    std::unique_ptr<Node> root_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
