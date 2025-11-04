#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <iterator>
#include <memory>
#include <vector>
#include <string>
#include <utility>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using node_type = binary_tree<T>;
    using node_ptr = std::unique_ptr<node_type>;

    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
    ~binary_tree() = default;
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    const T& data() const noexcept { return data_; }

    const node_ptr& left() const noexcept { return left_; }
    const node_ptr& right() const noexcept { return right_; }

    void insert(const T& value) {
        node_type* current = this;
        for (;;) {
            if ((value <= current->data_)) {
                if ((current->left_ == nullptr)) {
                    current->left_ = std::make_unique<node_type>(value);
                    return;
                } else {
                    current = current->left_.get();
                }
            } else {
                if ((current->right_ == nullptr)) {
                    current->right_ = std::make_unique<node_type>(value);
                    return;
                } else {
                    current = current->right_.get();
                }
            }
        }
    }

    class in_order_const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        in_order_const_iterator() = default;
        explicit in_order_const_iterator(const node_type* root) { push_left(root); }

        reference operator*() const noexcept { return stack_.back()->data_; }
        pointer operator->() const noexcept { return &(stack_.back()->data_); }

        in_order_const_iterator& operator++() {
            advance();
            return *this;
        }

        in_order_const_iterator operator++(int) {
            in_order_const_iterator tmp(*this);
            (void)++(*this);
            return tmp;
        }

        friend bool operator==(const in_order_const_iterator& a, const in_order_const_iterator& b) noexcept {
            return (a.stack_ == b.stack_);
        }

        friend bool operator!=(const in_order_const_iterator& a, const in_order_const_iterator& b) noexcept {
            return (!(a == b));
        }

    private:
        std::vector<const node_type*> stack_{};

        void push_left(const node_type* node) {
            const node_type* current = node;
            while ((current != nullptr)) {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }

        void advance() {
            if ((stack_.empty())) {
                return;
            } else {
                const node_type* node = stack_.back();
                stack_.pop_back();
                if ((node->right_ != nullptr)) {
                    push_left(node->right_.get());
                } else {
                    // no action
                }
            }
        }
    };

    in_order_const_iterator begin() const noexcept { return in_order_const_iterator(this); }
    in_order_const_iterator end() const noexcept { return in_order_const_iterator(); }

private:
    T data_;
    node_ptr left_;
    node_ptr right_;
};

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;

    void insert(std::int32_t value);
    bool contains(std::int32_t value) const;
    bool search(std::int32_t value) const;
    std::vector<std::int32_t> in_order() const;

private:
    struct Node {
        std::int32_t value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(std::int32_t v) : value(v), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root_ = nullptr;

    void in_order_traverse(const Node* node, std::vector<std::int32_t>& out) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
