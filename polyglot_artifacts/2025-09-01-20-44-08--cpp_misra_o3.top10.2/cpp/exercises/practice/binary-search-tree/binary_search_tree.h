#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>

namespace binary_search_tree {

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&)            = delete;
    BinarySearchTree(BinarySearchTree&&)                 = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&)      = delete;
    ~BinarySearchTree()                                  = default;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node {
        explicit Node(std::int32_t v) : value(v), left(nullptr), right(nullptr) {}

        std::int32_t               value;
        std::unique_ptr<Node>      left;
        std::unique_ptr<Node>      right;
    };

    std::unique_ptr<Node> root_{nullptr};

    static void insertNode(std::unique_ptr<Node>& current, std::int32_t value);
    [[nodiscard]] static bool containsNode(const std::unique_ptr<Node>& current, std::int32_t value);
};

template <typename T>
class binary_tree
{
    /* disallow narrow character-sized integral types that violate MISRA rule
       (use fixed-width <cstdint> types instead) */
    static_assert(!std::is_same_v<T, std::int8_t> &&
                  !std::is_same_v<T, std::uint8_t>,
                  "8-bit character types are not supported.");

public:
    using value_type = T;

    explicit binary_tree(const value_type& value) :
        value_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    binary_tree(const binary_tree&)            = delete;
    binary_tree(binary_tree&&)                 = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree& operator=(binary_tree&&)      = delete;
    ~binary_tree()                             = default;

    void insert(const value_type& value)
    {
        /* tree structure changes – rebuild traversal cache on next iteration */
        traversal_cache_.reset();

        if((value <= value_)) {
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

    [[nodiscard]] const value_type& data() const noexcept
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

private:
    class iterator_impl;

public:
    class iterator
    {
        using pointer   = const value_type*;
        using vec_type  = std::vector<pointer>;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using reference         = const value_type&;

        iterator() :
            nodes_(nullptr),
            index_(0U)
        {
        }

        iterator(const std::shared_ptr<vec_type>& nodes, std::size_t idx) :
            nodes_(nodes),
            index_(idx)
        {
        }

        reference operator*() const
        {
            return *(*nodes_)[index_];
        }

        pointer operator->() const
        {
            return (*nodes_)[index_];
        }

        iterator& operator++()
        {
            ++index_;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            return ((lhs.nodes_ == rhs.nodes_) && (lhs.index_ == rhs.index_));
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::shared_ptr<vec_type> nodes_;
        std::size_t               index_;
    };

    [[nodiscard]] iterator begin() const
    {
        /* build cache lazily to make begin() and end() share the same sequence */
        if(traversal_cache_ == nullptr) {
            traversal_cache_ = std::make_shared<std::vector<const value_type*>>();
            fill_in_order(traversal_cache_.get());
        }
        return iterator(traversal_cache_, 0U);
    }

    [[nodiscard]] iterator end() const
    {
        if(traversal_cache_ == nullptr) {
            traversal_cache_ = std::make_shared<std::vector<const value_type*>>();
            fill_in_order(traversal_cache_.get());
        }
        return iterator(traversal_cache_, traversal_cache_->size());
    }

private:
    void fill_in_order(std::vector<const value_type*>* out) const
    {
        if(left_ != nullptr) {
            left_->fill_in_order(out);
        }
        out->push_back(&value_);
        if(right_ != nullptr) {
            right_->fill_in_order(out);
        }
    }

    value_type                      value_;
    std::unique_ptr<binary_tree>    left_;
    std::unique_ptr<binary_tree>    right_;
    mutable std::shared_ptr<std::vector<const value_type*>> traversal_cache_;
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values)
{
    if(values.empty()) {
        return nullptr;
    }

    auto root = std::make_unique<binary_tree<T>>(values.front());
    for(std::size_t idx = 1U; idx < values.size(); ++idx) {
        root->insert(values[idx]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
