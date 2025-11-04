#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <iterator>
#include <vector>

namespace binary_search_tree {

// -----------------------------------------------------------------------------
// A generic binary search tree that supports insertion, membership queries and
// in-order iteration.  The tree stores values of arbitrary comparable type T.
// -----------------------------------------------------------------------------
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : data_(value) {}

    // Disable copy semantics to keep ownership unique.
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(binary_tree&&) = default;

    // Insert a value into the correct place in the tree.
    void insert(const T& value) {
        if (value <= data_) {
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

    // Return true if value is present.
    bool contains(const T& value) const {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // Accessors ---------------------------------------------------------------
    const T& data() const { return data_; }
    const binary_tree* left()  const { return left_.get(); }
    const binary_tree* right() const { return right_.get(); }

    // In-order const iteration ------------------------------------------------
    using container_type = std::vector<T>;
    using const_iterator = typename container_type::const_iterator;

    const_iterator begin() const {
        cache_.clear();
        fill_in_order(cache_);
        return cache_.begin();
    }
    const_iterator end() const {
        return cache_.end();
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{nullptr};
    std::unique_ptr<binary_tree<T>> right_{nullptr};

    // mutable so that begin() can refresh it from a const context
    mutable container_type cache_;

    void fill_in_order(container_type& vec) const {
        if (left_)  left_->fill_in_order(vec);
        vec.push_back(data_);
        if (right_) right_->fill_in_order(vec);
    }
};

// A simple binary search tree that supports insertion and membership queries
class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    // Disable copy semantics to avoid shallow copies of the underlying nodes.
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Insert a value into the tree.
    void insert(int value);

    // Return true if value is present in the tree, false otherwise.
    bool contains(int value) const;

private:
    struct Node;
    Node* root_{nullptr};

    Node* insert(Node* node, int value);
    bool contains(Node* node, int value) const;
    void destroy(Node* node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
