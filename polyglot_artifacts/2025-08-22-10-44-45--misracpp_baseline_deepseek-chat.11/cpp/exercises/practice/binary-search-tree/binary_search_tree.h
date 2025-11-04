#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    // Constructor
    binary_tree() : root(nullptr) {}
    // Constructor with data
    binary_tree(T data) : root(new Node(data)) {}
    // Copy constructor
    binary_tree(const binary_tree& other);
    // Assignment operator
    binary_tree& operator=(const binary_tree& other);
    // Destructor
    ~binary_tree();
    
    // Insert a value
    void insert(T value);
    
    // Find a value
    bool find(T value) const;
    
    // Get root data
    T data() const;
    
    // Get left and right subtrees
    binary_tree* left() const;
    binary_tree* right() const;
    
    // Operator to check if the tree is non-empty
    explicit operator bool() const;

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Helper functions
    Node* insert(Node* node, T value);
    bool find(Node* node, T value) const;
    // Helper for deep copy
    Node* copy_tree(Node* other_node);
    // Helper for destruction
    void destroy_tree(Node* node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
