#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <cstdint>
#include <memory>
#include <cstddef>
#include <vector>
#include <iterator>

namespace binary_search_tree {

class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;

    void insert(std::int32_t value);

    bool contains(std::int32_t value) const;

private:
    struct Node {
        explicit Node(std::int32_t value_in) : value(value_in) {}

        std::int32_t value;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    void insert_impl(std::unique_ptr<Node>& current, std::int32_t value);
    bool contains_impl(const std::unique_ptr<Node>& current, std::int32_t value) const;

    std::unique_ptr<Node> root_{nullptr};
};

template<typename T>
class binary_tree {
public:
    binary_tree() noexcept = default;
    explicit binary_tree(const T& value_in) : value_(value_in), has_value_(true) {}

    void insert(const T& value_in)
    {
        if (!has_value_) {
            value_ = value_in;
            has_value_ = true;
        } else {
            if (value_in <= value_) {
                if (left_ == nullptr) {
                    left_ = std::make_unique<binary_tree<T>>(value_in);
                } else {
                    left_->insert(value_in);
                }
            } else {
                if (right_ == nullptr) {
                    right_ = std::make_unique<binary_tree<T>>(value_in);
                } else {
                    right_->insert(value_in);
                }
            }
        }
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return value_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        iterator() noexcept = default;

        explicit iterator(const binary_tree<T>* root)
        {
            push_left(root);
        }

        reference operator*() const
        {
            return stack_.back()->value_;
        }

        pointer operator->() const
        {
            return &(stack_.back()->value_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            static_cast<void>(++(*this));
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) noexcept
        {
            if ((lhs.stack_.empty()) && (rhs.stack_.empty())) {
                return true;
            }
            if ((lhs.stack_.empty()) || (rhs.stack_.empty())) {
                return false;
            }
            return (lhs.stack_.back() == rhs.stack_.back());
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while ((current != nullptr) && (current->has_value_)) {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }

        std::vector<const binary_tree<T>*> stack_;
    };

    iterator begin() const
    {
        return iterator(this);
    }

    iterator end() const noexcept
    {
        return iterator();
    }

private:
    T value_{};
    bool has_value_{false};
    std::unique_ptr<binary_tree<T>> left_{nullptr};
    std::unique_ptr<binary_tree<T>> right_{nullptr};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
