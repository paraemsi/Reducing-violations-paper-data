#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() = default;
    explicit binary_tree(T data);
    
    // Insert a value into the tree
    void insert(T value);
    // Check if a value exists in the tree
    bool contains(T value) const;
    // Get the root data
    T data() const;
    // Get left and right subtrees
    binary_tree<T>* left() const;
    binary_tree<T>* right() const;

private:
    T data_{};
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
