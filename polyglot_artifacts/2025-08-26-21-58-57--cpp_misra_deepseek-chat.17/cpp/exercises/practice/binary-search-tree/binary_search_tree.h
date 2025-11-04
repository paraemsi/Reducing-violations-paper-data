#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // The tree will always have data, so we need to construct it with data
    explicit binary_tree(T data) : data_(data) {}
    // Insert a value into the tree
    void insert(T value);
    // Search for a value in the tree
    bool contains(T value) const;
    // Get the root data
    T data() const;
    // Get left and right subtrees
    std::unique_ptr<binary_tree<T>> left() const;
    std::unique_ptr<binary_tree<T>> right() const;

private:
    // Private default constructor for internal use
    binary_tree() = default;
    T data_{};
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
