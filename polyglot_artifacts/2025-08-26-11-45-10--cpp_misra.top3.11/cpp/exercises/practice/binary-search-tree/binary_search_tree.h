#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <stack>
#include <type_traits>

namespace binary_search_tree {

using bst_value_t = std::int32_t;

// Legacy Node and BinarySearchTree for backward compatibility
struct Node
{
    bst_value_t value;
    Node* left;
    Node* right;

    explicit Node(bst_value_t v);
    ~Node();
};

class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(bst_value_t value);
    bool search(bst_value_t value) const;

private:
    Node* root;

    void insert(Node*& node, bst_value_t value);
    bool search(const Node* node, bst_value_t value) const;
    void destroy(Node* node);
};

/*
 * Modern generic binary_tree for test compatibility
 */
template <typename T>
class binary_tree {
public:
    using value_type = T;
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& data)
        : data_(data), left_(nullptr), right_(nullptr) {}

    const T& data() const { return data_; }

    const tree_ptr& left() const { return left_; }
    const tree_ptr& right() const { return right_; }

    void insert(const T& value) {
        if (value <= data_) {
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

    // In-order iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() : current_(nullptr), value_(nullptr) {}

        explicit iterator(const binary_tree<T>* root) : current_(nullptr), value_(nullptr) {
            push_left(root);
            advance();
        }

        reference operator*() const { return *value_; }
        pointer operator->() const { return value_; }

        iterator& operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return (current_ == other.current_) && (stack_ == other.stack_) && (value_ == other.value_);
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        const binary_tree<T>* current_;
        std::stack<const binary_tree<T>*> stack_;
        const T* value_;

        void push_left(const binary_tree<T>* node) {
            while (node != nullptr) {
                stack_.push(node);
                node = node->left_.get();
            }
        }

        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                value_ = nullptr;
                return;
            }
            current_ = stack_.top();
            stack_.pop();
            value_ = &(current_->data_);
            if (current_->right_) {
                push_left(current_->right_.get());
            }
        }
    };

    iterator begin() const { return iterator(this); }
    iterator end() const { return iterator(); }

private:
    T data_;
    tree_ptr left_;
    tree_ptr right_;
};

// Helper function to build a tree from a vector
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    if (data.empty()) {
        return nullptr;
    }
    auto root = std::make_unique<binary_tree<T>>(data[0]);
    for (std::size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
