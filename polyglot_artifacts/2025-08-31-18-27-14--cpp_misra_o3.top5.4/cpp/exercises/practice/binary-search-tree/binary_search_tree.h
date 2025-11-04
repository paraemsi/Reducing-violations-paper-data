#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <initializer_list>

namespace binary_search_tree {

class BinarySearchTree final {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value);
    bool contains(std::int32_t value) const;

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) = delete;

private:
    struct Node {
        explicit Node(std::int32_t value) noexcept
            : data(value), left(nullptr), right(nullptr) {}

        std::int32_t data;
        Node* left;
        Node* right;
    };

    Node* root_{ nullptr };

    static void destroy_subtree(Node* node) noexcept;
    static Node* insert(Node* node, std::int32_t value);
    static bool contains(const Node* node, std::int32_t value) noexcept;
};

/*
 * Generic binary search-tree that the unit-tests expect.
 * Implemented entirely in the header so the template can be instantiated
 * by the test TU.  All operations follow the same insertion semantics as
 * BinarySearchTree above: values less-than-or-equal go to the left, greater
 * to the right.
 */
template<typename T>
class binary_tree final {
public:
    explicit binary_tree(const T& value) : data_{ value } {}

    /* observers ---------------------------------------------------------- */
    const T& data() const noexcept { return data_; }

    std::unique_ptr<binary_tree>& left() noexcept { return left_; }
    const std::unique_ptr<binary_tree>& left() const noexcept { return left_; }

    std::unique_ptr<binary_tree>& right() noexcept { return right_; }
    const std::unique_ptr<binary_tree>& right() const noexcept { return right_; }

    /* modifiers ---------------------------------------------------------- */
    void insert(const T& value)
    {
        if ((value <= data_) ) {
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

    bool contains(const T& value) const
    {
        if (value == data_) {
            return true;
        }

        if (value < data_) {
            return (left_ != nullptr) && (left_->contains(value));
        }

        return (right_ != nullptr) && (right_->contains(value));
    }

    /* in-order iterator -------------------------------------------------- */
    class iterator {
        using node_ptr = binary_tree*;

        void push_left(node_ptr node)
        {
            while (node != nullptr) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;
        explicit iterator(node_ptr root) { push_left(root); }

        reference operator*() const { return stack_.back()->data_; }
        pointer   operator->() const { return &(stack_.back()->data_); }

        iterator& operator++() /* pre-increment */
        {
            node_ptr current = stack_.back();
            stack_.pop_back();
            push_left(current->right_.get());
            return *this;
        }

        iterator operator++(int) /* NOLINT(readability-identifier-naming) */
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
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
        std::vector<node_ptr> stack_{};
    };

    class const_iterator {
        using node_ptr = const binary_tree*;

        void push_left(node_ptr node)
        {
            while (node != nullptr) {
                stack_.push_back(node);
                node = node->left_.get();
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() = default;
        explicit const_iterator(node_ptr root) { push_left(root); }

        reference operator*() const { return stack_.back()->data_; }
        pointer   operator->() const { return &(stack_.back()->data_); }

        const_iterator& operator++()
        {
            node_ptr current = stack_.back();
            stack_.pop_back();
            push_left(current->right_.get());
            return *this;
        }

        const_iterator operator++(int) /* NOLINT(readability-identifier-naming) */
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
        {
            return lhs.stack_ == rhs.stack_;
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::vector<node_ptr> stack_{};
    };

    iterator begin() noexcept { return iterator(this); }
    iterator end() noexcept { return iterator(); }

    const_iterator begin() const noexcept { return const_iterator(this); }
    const_iterator end() const noexcept { return const_iterator(); }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

/*
 * Convenience helper used by the unit-tests to build a tree from a range.
 */
template<typename T, typename Range>
std::unique_ptr<binary_tree<T>> make_tree_from_range(const Range& values)
{
    if (values.begin() == values.end()) {
        return nullptr;
    }

    auto iter = values.begin();
    std::unique_ptr<binary_tree<T>> root = std::make_unique<binary_tree<T>>(*iter);
    ++iter;

    for (; iter != values.end(); ++iter) {
        root->insert(*iter);
    }

    return root;
}

/*
 * Overload for initializer-list so the tests can write:
 * auto t = make_tree<uint32_t>({4,2,6});
 */
template<typename T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> init)
{
    return make_tree_from_range<T>(init);
}

} // namespace binary_search_tree

// Expose make_tree in the global namespace so that the unit tests can call it
// without qualification while still keeping the implementation inside the
// binary_search_tree namespace.
using binary_search_tree::make_tree;

#endif // BINARY_SEARCH_TREE_H
