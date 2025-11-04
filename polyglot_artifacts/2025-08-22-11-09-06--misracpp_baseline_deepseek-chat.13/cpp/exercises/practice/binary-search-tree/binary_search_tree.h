#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    // Constructor
    binary_tree() : root(nullptr) {}
    // Insert a value
    void insert(const T& value);
    // Search for a value
    T* find(const T& value) const;
    // Get root data
    T data() const;
    // Get left and right subtrees
    binary_tree<T>* left() const;
    binary_tree<T>* right() const;
    
    // Destructor to clean up memory
    ~binary_tree();
    
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
    Node* find(Node* node, const T& value) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
