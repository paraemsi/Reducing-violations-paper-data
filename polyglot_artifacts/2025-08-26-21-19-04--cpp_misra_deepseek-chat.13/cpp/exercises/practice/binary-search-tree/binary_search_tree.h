#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>

namespace binary_search_tree {

template<typename T>
class TreeNode {
public:
    T data;
    std::unique_ptr<TreeNode<T>> left;
    std::unique_ptr<TreeNode<T>> right;
    
    explicit TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    
    const TreeNode<T>* left() const {
        return left.get();
    }
    
    const TreeNode<T>* right() const {
        return right.get();
    }
    
    T data() const {
        return this->data;
    }
};

template<typename T>
class binary_tree {
private:
    std::unique_ptr<TreeNode<T>> root;
    
    void insert(std::unique_ptr<TreeNode<T>>& node, const T& value) {
        if (!node) {
            node = std::make_unique<TreeNode<T>>(value);
            return;
        }
        if ((value <= node->data)) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }
    
    const TreeNode<T>* find(const std::unique_ptr<TreeNode<T>>& node, const T& value) const {
        if (!node) {
            return nullptr;
        }
        if ((node->data == value)) {
            return node.get();
        }
        if ((value < node->data)) {
            return find(node->left, value);
        } else {
            return find(node->right, value);
        }
    }
    
public:
    binary_tree() : root(nullptr) {}
    
    void insert(const T& value) {
        insert(root, value);
    }
    
    const TreeNode<T>* find(const T& value) const {
        return find(root, value);
    }
    
    const TreeNode<T>* left() const {
        return root ? root->left.get() : nullptr;
    }
    
    const TreeNode<T>* right() const {
        return root ? root->right.get() : nullptr;
    }
    
    T data() const {
        return root->data;
    }
    
    const TreeNode<T>* get_root() const {
        return root.get();
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
