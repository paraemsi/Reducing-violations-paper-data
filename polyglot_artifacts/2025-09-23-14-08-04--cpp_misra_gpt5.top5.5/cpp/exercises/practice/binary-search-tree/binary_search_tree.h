#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

namespace binary_search_tree {

// Templated binary search tree supporting insertion, search, and in-order iteration.
template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const value_type& value) : data_{value}, left_{}, right_{} {}

    void insert(const value_type& value) {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            } else {
                right_->insert(value);
            }
        }
    }

    bool contains(const value_type& value) const {
        if ((value == data_)) {
            return true;
        }
        if ((value < data_)) {
            if ((left_ != nullptr)) {
                return left_->contains(value);
            } else {
                return false;
            }
        } else {
            if ((right_ != nullptr)) {
                return right_->contains(value);
            } else {
                return false;
            }
        }
    }

    const value_type& data() const noexcept { return data_; }

    const binary_tree<T>* left() const noexcept { return left_.get(); }

    const binary_tree<T>* right() const noexcept { return right_.get(); }

    // Non-const in-order iterator
    class iterator {
    public:
        using value_type = T;
        using reference = T&;

        iterator() = default;

        explicit iterator(binary_tree<T>* root) {
            push_left(root);
        }

        reference operator*() const {
            return stack_.back()->data_;
        }

        iterator& operator++() {
            binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if ((node->right_ != nullptr)) {
                push_left(node->right_.get());
            }
            return *this;
        }

        bool operator==(const iterator& other) const noexcept {
            if ((stack_.empty()) && (other.stack_.empty())) {
                return true;
            }
            if ((!stack_.empty()) && (!other.stack_.empty())) {
                return (stack_.back() == other.stack_.back());
            }
            return false;
        }

        bool operator!=(const iterator& other) const noexcept {
            return (!(*this == other));
        }

    private:
        std::vector<binary_tree<T>*> stack_{};

        void push_left(binary_tree<T>* node) {
            binary_tree<T>* cur = node;
            while ((cur != nullptr)) {
                stack_.push_back(cur);
                if ((cur->left_ != nullptr)) {
                    cur = cur->left_.get();
                } else {
                    cur = nullptr;
                }
            }
        }
    };

    // Const in-order iterator
    class const_iterator {
    public:
        using value_type = T;
        using reference = const T&;

        const_iterator() = default;

        explicit const_iterator(const binary_tree<T>* root) {
            push_left(root);
        }

        reference operator*() const {
            return stack_.back()->data_;
        }

        const_iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if ((node->right_ != nullptr)) {
                push_left(node->right_.get());
            }
            return *this;
        }

        bool operator==(const const_iterator& other) const noexcept {
            if ((stack_.empty()) && (other.stack_.empty())) {
                return true;
            }
            if ((!stack_.empty()) && (!other.stack_.empty())) {
                return (stack_.back() == other.stack_.back());
            }
            return false;
        }

        bool operator!=(const const_iterator& other) const noexcept {
            return (!(*this == other));
        }

    private:
        std::vector<const binary_tree<T>*> stack_{};

        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* cur = node;
            while ((cur != nullptr)) {
                stack_.push_back(cur);
                if ((cur->left_ != nullptr)) {
                    cur = cur->left_.get();
                } else {
                    cur = nullptr;
                }
            }
        }
    };

    iterator begin() {
        return iterator(this);
    }

    iterator end() noexcept {
        return iterator();
    }

    const_iterator begin() const {
        return const_iterator(this);
    }

    const_iterator end() const noexcept {
        return const_iterator();
    }

private:
    value_type data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

// Node of a Binary Search Tree storing 32-bit signed integers.
class Node {
public:
    using value_type = std::int32_t;

    explicit Node(value_type value) noexcept;

    // Insert value into the subtree rooted at this node.
    void insert(value_type value);

    // Search for value in the subtree rooted at this node.
    bool contains(value_type value) const noexcept;

    // Accessors
    value_type data() const noexcept;
    const Node* left() const noexcept;
    const Node* right() const noexcept;

private:
    value_type data_{0};
    std::unique_ptr<Node> left_{};
    std::unique_ptr<Node> right_{};
};

// A Binary Search Tree wrapper to manage the root node.
class BinarySearchTree {
public:
    using value_type = Node::value_type;

    BinarySearchTree() = default;

    // Insert value into the tree (creates root if empty).
    void insert(value_type value);

    // Check if the tree contains value.
    bool contains(value_type value) const noexcept;

    // Root accessor (const).
    const Node* root() const noexcept;

private:
    std::unique_ptr<Node> root_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
