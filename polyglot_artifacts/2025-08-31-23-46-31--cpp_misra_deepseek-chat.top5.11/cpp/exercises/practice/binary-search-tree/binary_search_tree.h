#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(T value);
    bool contains(T value) const;
    const T& data() const;
    const binary_tree* left() const;
    const binary_tree* right() const;
    
    // Iterator support
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : current(nullptr) {}
        explicit iterator(Node* root);
        
        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        
    private:
        Node* current;
        std::vector<Node*> stack;
        
        void push_left(Node* node);
    };
    
    iterator begin() const;
    iterator end() const;

private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        explicit Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    void insert_impl(std::unique_ptr<Node>& node, T value);
    bool contains_impl(const std::unique_ptr<Node>& node, T value) const;
    
    // Helper function to deep copy a node and its children
    static std::unique_ptr<Node> copy_node(const std::unique_ptr<Node>& node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
