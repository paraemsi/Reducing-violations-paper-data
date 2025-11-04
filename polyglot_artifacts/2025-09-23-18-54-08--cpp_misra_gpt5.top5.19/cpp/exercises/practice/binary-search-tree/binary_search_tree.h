#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

class BinarySearchTree final {
public:
    BinarySearchTree() noexcept = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() noexcept = default;

    void insert(std::int32_t value);
    bool contains(std::int32_t value) const noexcept;

private:
    struct Node final {
        explicit Node(std::int32_t v) noexcept : value(v), left(nullptr), right(nullptr) {}
        std::int32_t value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root_{};

    static void insert_node(std::unique_ptr<Node>& node, std::int32_t value);
    static bool contains_node(const std::unique_ptr<Node>& node, std::int32_t value) noexcept;
};

template <typename T>
class binary_tree final {
public:
    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}

    const T& data() const noexcept
    {
        return data_;
    }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

    void insert(const T& value)
    {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    class const_iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::int32_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() noexcept = default;

        explicit const_iterator(const binary_tree<T>* root) noexcept
        {
            push_left(root);
        }

        reference operator*() const noexcept
        {
            return (node_stack_.back()->data_);
        }

        pointer operator->() const noexcept
        {
            return (&(node_stack_.back()->data_));
        }

        const_iterator& operator++() noexcept
        {
            const binary_tree<T>* node = node_stack_.back();
            node_stack_.pop_back();

            if ((node->right_.get() != nullptr)) {
                push_left(node->right_.get());
            }

            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            const_iterator tmp = *this;
            (void)++(*this);
            return (tmp);
        }

        friend bool operator==(const const_iterator& a, const const_iterator& b) noexcept
        {
            if ((a.node_stack_.empty()) && (b.node_stack_.empty())) {
                return true;
            }

            if ((a.node_stack_.empty()) || (b.node_stack_.empty())) {
                return false;
            }

            return (a.node_stack_.back() == b.node_stack_.back());
        }

        friend bool operator!=(const const_iterator& a, const const_iterator& b) noexcept
        {
            return (!(a == b));
        }

    private:
        void push_left(const binary_tree<T>* node) noexcept
        {
            const binary_tree<T>* cur = node;
            while ((cur != nullptr)) {
                node_stack_.push_back(cur);
                cur = cur->left_.get();
            }
        }

        std::vector<const binary_tree<T>*> node_stack_;
    };

    const_iterator begin() const noexcept
    {
        return (const_iterator(this));
    }

    const_iterator end() const noexcept
    {
        return (const_iterator());
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
