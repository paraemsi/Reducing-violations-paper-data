#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstddef>
#include <memory>
#include <vector>
#include <optional>
#include <stdexcept>

namespace binary_search_tree {

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    // Disable copy semantics to keep ownership simple.
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Insert a value into the tree. Duplicates go to the left subtree.
    void insert(int value);

    // Check whether the tree contains a value.
    bool contains(int value) const;

private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        explicit Node(int v) : data(v), left(nullptr), right(nullptr) {}
    };

    Node* root_{nullptr};

    static void insert(Node*& node, int value);
    static bool contains(const Node* node, int value);
    static void destroy(Node* node);
};

// Generic templated binary search tree used by the tests.
template <typename T>
class binary_tree {
public:
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& value) : data_{value} {}

    // Prevent copying to keep ownership simple.
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    // Insert a value into the tree. Duplicates go to the left subtree.
    void insert(const T& value) {
        if (!data_) {
            data_ = value;
            return;
        }
        if (value <= *data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    // Check whether the tree contains a value.
    bool contains(const T& value) const {
        if (!data_) {
            return false;
        }
        if (value == *data_) {
            return true;
        }
        if (value < *data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // Accessors required by the tests.
    const T& data() const {
        if (!data_) {
            throw std::runtime_error("empty tree has no data");
        }
        return *data_;
    }

    const tree_ptr& left() const noexcept  { return left_;  }
    const tree_ptr& right() const noexcept { return right_; }

    // Range-based for support (in-order traversal).
    auto begin() const {
        traversal_.clear();
        fill_inorder(this, traversal_);
        return traversal_.cbegin();
    }

    auto end() const {
        return traversal_.cend();
    }

private:
    static void fill_inorder(const binary_tree<T>* node, std::vector<T>& out) {
        if (!node || !node->data_) {
            return;
        }
        fill_inorder(node->left_.get(),  out);
        out.push_back(*node->data_);
        fill_inorder(node->right_.get(), out);
    }

    std::optional<T> data_;
    tree_ptr left_{};
    tree_ptr right_{};
    mutable std::vector<T> traversal_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
