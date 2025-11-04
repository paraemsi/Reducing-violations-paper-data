#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Constructor that takes a value
    explicit binary_tree(const T& value) : root(std::make_unique<Node>(value)) {}
    binary_tree() = default;
    
    // Insert a value
    void insert(const T& value);
    
    // Search for a value
    bool contains(const T& value) const;
    
    // Get root data
    const T& data() const;
    
    // Get left and right subtrees
    binary_tree* left() const;
    binary_tree* right() const;
    
    // For boolean context
    explicit operator bool() const { return root != nullptr; }

private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    // Helper functions
    void insert_helper(std::unique_ptr<Node>& node, const T& value);
    bool contains_helper(const std::unique_ptr<Node>& node, const T& value) const;
    
    // Helper to deep copy a node and its children
    static std::unique_ptr<Node> copy_tree(const std::unique_ptr<Node>& node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
