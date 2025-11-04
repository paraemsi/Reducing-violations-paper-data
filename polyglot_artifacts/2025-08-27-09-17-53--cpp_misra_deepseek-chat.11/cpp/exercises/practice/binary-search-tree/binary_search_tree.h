#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>

namespace binary_search_tree {

template<typename T>
class binary_tree;

template<typename T>
struct TreeNode {
    T data_;
    std::unique_ptr<TreeNode<T>> left_;
    std::unique_ptr<TreeNode<T>> right_;
    
    explicit TreeNode(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    const T& data() const { return data_; }
    const TreeNode<T>* left() const { return left_.get(); }
    const TreeNode<T>* right() const { return right_.get(); }
};

template<typename T>
class binary_tree {
public:
    binary_tree() : root_(nullptr) {}
    
    void insert(const T& value) {
        insert_impl(root_, value);
    }
    
    const TreeNode<T>* find(const T& value) const {
        return find_impl(root_.get(), value);
    }
    
    const TreeNode<T>* get_root() const {
        return root_.get();
    }

private:
    std::unique_ptr<TreeNode<T>> root_;
    
    void insert_impl(std::unique_ptr<TreeNode<T>>& node, const T& value) {
        if (!node) {
            node = std::make_unique<TreeNode<T>>(value);
            return;
        }
        
        if ((value <= node->data_)) {
            insert_impl(node->left_, value);
        } else {
            insert_impl(node->right_, value);
        }
    }
    
    const TreeNode<T>* find_impl(const TreeNode<T>* node, const T& value) const {
        if (!node) {
            return nullptr;
        }
        
        if ((value == node->data_)) {
            return node;
        } else if ((value < node->data_)) {
            return find_impl(node->left(), value);
        } else {
            return find_impl(node->right(), value);
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
