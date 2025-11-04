#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Constructor
    binary_tree() : root(nullptr) {}
    
    // Insert a value
    void insert(T value);
    
    // Search for a value
    bool find(T value) const;
    
    // Get the root data
    T data() const;
    
    // Get left and right subtrees
    std::unique_ptr<binary_tree<T>> left() const;
    std::unique_ptr<binary_tree<T>> right() const;
    
    // Iteration support
    // To support range-based for loops, we need to provide begin() and end()
    // We'll use the in-order traversal
    // Let's use a vector to store the elements and return its iterators
    std::vector<T> get_elements_in_order() const;
    void in_order_traversal_helper(const std::unique_ptr<Node>& node, std::vector<T>& result) const;
    
    // begin() and end() for range-based for loops
    typename std::vector<T>::const_iterator begin() const { 
        return get_elements_in_order().begin(); 
    }
    typename std::vector<T>::const_iterator end() const { 
        return get_elements_in_order().end(); 
    }

private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    // Helper functions
    void insert_helper(std::unique_ptr<Node>& node, T value);
    bool find_helper(const std::unique_ptr<Node>& node, T value) const;
    // Helper function to copy a node recursively
    std::unique_ptr<Node> copy_node(const std::unique_ptr<Node>& node) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
