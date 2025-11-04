#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>
#include <string>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    explicit binary_tree(const T& value) : data_{value} {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;

    ~binary_tree() = default;

    /* insert ----------------------------------------------------------------*/
    void insert(const T& value) {
        if (value <= data_) {
            if (left_ == nullptr) {
                left_ = std::make_unique<binary_tree>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if (right_ == nullptr) {
                right_ = std::make_unique<binary_tree>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    /* observers -------------------------------------------------------------*/
    [[nodiscard]] const T& data() const noexcept { return data_; }

    [[nodiscard]] const std::unique_ptr<binary_tree>& left() const noexcept {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree>& right() const noexcept {
        return right_;
    }

    /* iterator --------------------------------------------------------------*/
    class iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() = default;

        reference operator*() const noexcept { return *nodes_[index_]; }
        pointer operator->() const noexcept { return nodes_[index_]; }

        iterator& operator++() noexcept {
            ++index_;
            return *this;
        }

        iterator operator++(int) noexcept {
            iterator tmp{*this};
            ++(*this);
            return tmp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) noexcept {
            return (lhs.index_ == rhs.index_) && (lhs.nodes_ == rhs.nodes_);
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) noexcept {
            return !(lhs == rhs);
        }

    private:
        explicit iterator(const binary_tree* root) { build_inorder(root); }

        void build_inorder(const binary_tree* node) {
            if (node == nullptr) {
                return;
            }
            build_inorder(node->left_.get());
            nodes_.push_back(&node->data_);
            build_inorder(node->right_.get());
        }

        std::vector<const T*> nodes_;
        std::size_t index_{0U};

        friend class binary_tree;
    };

    [[nodiscard]] iterator begin() const { return iterator{this}; }
    [[nodiscard]] iterator end() const {
        iterator it{this};
        it.index_ = it.nodes_.size();
        return it;
    }

private:
    T data_;
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};
};

class BinarySearchTree final {
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node {
        std::int32_t data;
        Node* left;
        Node* right;

        explicit Node(std::int32_t val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root_{nullptr};

    static void destroy_subtree(Node* node) noexcept;
    static Node* insert_node(Node* node, std::int32_t value);
    static bool contains_node(const Node* node, std::int32_t value);
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
