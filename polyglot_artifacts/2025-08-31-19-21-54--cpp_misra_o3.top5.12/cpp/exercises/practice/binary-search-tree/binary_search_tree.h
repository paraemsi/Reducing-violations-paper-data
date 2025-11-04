#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <utility>

namespace binary_search_tree {

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;

    using ValueType = std::int32_t;

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;

    void insert(ValueType value);
    bool contains(ValueType value) const;

private:
    struct Node {
        explicit Node(ValueType v) : data(v) { }

        ValueType data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root;

    static void insertNode(std::unique_ptr<Node>& current, ValueType value);
    static bool containsNode(const std::unique_ptr<Node>& current, ValueType value);
};

/* -------------------------------------------------------------------------
 * Generic binary search tree – template version expected by the tests
 * --------------------------------------------------------------------- */
template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value) : value_{value} { }

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    void insert(const T& v) {
        if ((v <= value_)) {
            if (left_ == nullptr) {
                left_ = std::make_unique<binary_tree>(v);
            } else {
                left_->insert(v);
            }
        } else {
            if (right_ == nullptr) {
                right_ = std::make_unique<binary_tree>(v);
            } else {
                right_->insert(v);
            }
        }

        /* traversal cache no longer valid after structural change */
        traversal_cache_.reset();
    }

    bool contains(const T& v) const noexcept {
        bool result{false};

        if (v == value_) {
            result = true;
        } else {
            if (v < value_) {
                result = (left_ != nullptr) && (left_->contains(v));
            } else {
                result = (right_ != nullptr) && (right_->contains(v));
            }
        }
        return result;
    }

    const T& data() const noexcept {
        return value_;
    }

    const std::unique_ptr<binary_tree>& left() const noexcept {
        return left_;
    }

    const std::unique_ptr<binary_tree>& right() const noexcept {
        return right_;
    }

    /* ---------------- iterator support (in-order traversal) ----------- */
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() = default;

        iterator(std::shared_ptr<std::vector<T>> vec, std::size_t idx)
            : data_{std::move(vec)}, index_{idx} { }

        reference operator*() const {
            return (*data_)[index_];
        }

        pointer operator->() const {
            return &(*data_)[index_];
        }

        iterator& operator++() {
            ++index_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp{*this};
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return ((data_ == other.data_) && (index_ == other.index_));
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        std::shared_ptr<std::vector<T>> data_;
        std::size_t index_{0U};
    };

    iterator begin() const {
        if (traversal_cache_ == nullptr) {
            traversal_cache_ = std::make_shared<std::vector<T>>();
            inorder_collect(this, traversal_cache_);
        }
        return iterator(traversal_cache_, 0U);
    }

    iterator end() const {
        if (traversal_cache_ == nullptr) {
            traversal_cache_ = std::make_shared<std::vector<T>>();
            inorder_collect(this, traversal_cache_);
        }
        return iterator(traversal_cache_, traversal_cache_->size());
    }

private:
    T value_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    mutable std::shared_ptr<std::vector<T>> traversal_cache_;

    static void inorder_collect(const binary_tree* node,
                                const std::shared_ptr<std::vector<T>>& vec) {
        if (node == nullptr) {
            return;
        }
        inorder_collect(node->left_.get(), vec);
        vec->push_back(node->value_);
        inorder_collect(node->right_.get(), vec);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
