#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <initializer_list>

namespace binary_search_tree {

// ──────────────────────────────────────────────────────────────
// Generic, templated binary search tree that is iterable
// ──────────────────────────────────────────────────────────────
template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value) : data_(value) {}

    // forbid copying, allow moving
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    // insert new value, duplicates go to the left (≤)
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }

    // accessors
    const T& data() const { return data_; }
    binary_tree* left()  const { return left_.get(); }
    binary_tree* right() const { return right_.get(); }

    // const in-order iterator
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;

        reference operator*() const { return current_->data(); }
        pointer   operator->() const { return &current_->data(); }

        const_iterator& operator++() {
            advance();
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator& a, const const_iterator& b) {
            return a.current_ == b.current_;
        }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) {
            return !(a == b);
        }

    private:
        const binary_tree* current_{nullptr};
        std::vector<const binary_tree*> stack_{};

        explicit const_iterator(const binary_tree* root) {
            push_left(root);
        }

        void push_left(const binary_tree* node) {
            // reset current_ until we discover the next node
            current_ = nullptr;
            const binary_tree* n = node;
            while (n) {
                stack_.push_back(n);
                n = n->left();
            }
            if (!stack_.empty()) {
                current_ = stack_.back();
                stack_.pop_back();
            }
        }

        void advance() {
            if (current_ == nullptr) {
                return;
            }
            const binary_tree* r = current_->right();
            push_left(r);
        }

        friend class binary_tree;
    };

    const_iterator begin() const {
        return const_iterator(this);
    }

    const_iterator end() const {
        return const_iterator();
    }

private:

    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    std::unique_ptr<binary_tree<T>> root;
    if (data.empty()) {
        return root;
    }
    root = std::make_unique<binary_tree<T>>(data.front());
    for (std::size_t i = 1; i < data.size(); ++i) {
        root->insert(data[i]);
    }
    return root;
}

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> data) {
    return make_tree(std::vector<T>(data));
}

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    // Disable copy semantics to avoid accidental double-free
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Enable move semantics
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    // Insert a value into the BST
    void insert(int value);

    // Return true if the value exists in the BST
    bool contains(int value) const;

private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        explicit Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root_{nullptr};

    static void insert(Node*& node, int value);
    static bool contains(const Node* node, int value);
    static void destroy(Node* node);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
