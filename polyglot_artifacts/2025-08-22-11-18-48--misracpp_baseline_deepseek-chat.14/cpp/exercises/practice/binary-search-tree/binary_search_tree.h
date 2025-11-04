#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Constructors
    binary_tree() : root(nullptr) {}
    binary_tree(const T& value) : root(new Node(value)) {}
    
    // Insert a value
    void insert(const T& value);
    
    // Check if a value exists
    bool contains(const T& value) const;
    
    // Get the root data
    const T& data() const;
    
    // Get left and right subtrees
    std::unique_ptr<binary_tree<T>> left() const;
    std::unique_ptr<binary_tree<T>> right() const;

    // Iteration support
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Helper functions
    void insert(Node*& node, const T& value);
    bool contains(Node* node, const T& value) const;
    void in_order_traversal(Node* node, std::vector<T>& result) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
