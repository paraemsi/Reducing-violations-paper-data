#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Insert a value into the tree
    void insert(const T& value);
    // Search for a value in the tree
    bool contains(const T& value) const;
    // Get the root data
    const T& data() const;
    // Get left subtree
    std::unique_ptr<binary_tree<T>> left() const;
    // Get right subtree
    std::unique_ptr<binary_tree<T>> right() const;
    
    // Copy constructor
    binary_tree(const binary_tree& other);
    
    // Default constructor
    binary_tree() = default;

    // Iterator support
    using iterator = typename std::vector<T>::const_iterator;
    iterator begin() const;
    iterator end() const;

private:
    T data_{};
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
    mutable std::vector<T> elements_;
    
    // Helper function to flatten the tree into a vector
    void flatten_in_order(std::vector<T>& result) const;
    void update_elements() const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
