#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : root(nullptr) {}
    
    void insert(T value);
    bool contains(T value) const;
    const T* data() const;
    const binary_tree* left() const;
    const binary_tree* right() const;
    
private:
    struct TreeNode {
        T data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        
        explicit TreeNode(T value) 
            : data(value), 
              left(nullptr), 
              right(nullptr) {}
    };
    
    std::unique_ptr<TreeNode> root;
    
    // Private constructor to wrap a node
    explicit binary_tree(std::unique_ptr<TreeNode> node) : root(std::move(node)) {}
    
    void insert_impl(std::unique_ptr<TreeNode>& node, T value);
    bool contains_impl(const std::unique_ptr<TreeNode>& node, T value) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
