#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <vector>
#include <type_traits>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using ptr_type = std::unique_ptr<binary_tree<T>>;

    binary_tree() = default;
    explicit binary_tree(const T& v) : value_(v), has_value_(true) {}

    // Insert a value into the tree
    void insert(const T& v) {
        if (!has_value_) {
            value_ = v;
            has_value_ = true;
            return;
        }
        if (v <= value_) {
            if (!left_) {
                left_ = std::make_unique<binary_tree<T>>();
            }
            left_->insert(v);
        } else {
            if (!right_) {
                right_ = std::make_unique<binary_tree<T>>();
            }
            right_->insert(v);
        }
    }

    // Return the value at this node
    const T& data() const { return value_; }

    // Return left child (may be nullptr)
    const ptr_type& left() const { return left_; }

    // Return right child (may be nullptr)
    const ptr_type& right() const { return right_; }

    // In-order iterator support
    class iterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::input_iterator_tag;

        iterator() : current_(nullptr) {}
        explicit iterator(const binary_tree<T>* node) { traverse(node); advance(); }

        reference operator*() const { return *current_; }
        pointer operator->() const { return current_; }

        iterator& operator++() { advance(); return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& other) const { return (stack_ == other.stack_) && (current_ == other.current_); }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        void traverse(const binary_tree<T>* node) {
            while (node) {
                if (node->has_value_) {
                    stack_.push_back(node);
                    node = node->left_.get();
                } else {
                    break;
                }
            }
        }
        void advance() {
            if (stack_.empty()) {
                current_ = nullptr;
                return;
            }
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            current_ = &(node->value_);
            if (node->right_) {
                traverse(node->right_.get());
            }
        }
        std::vector<const binary_tree<T>*> stack_;
        const T* current_ = nullptr;
    };

    iterator begin() const { return has_value_ ? iterator(this) : iterator(); }
    iterator end() const { return iterator(); }

    // For test compatibility: construct from vector
    static std::unique_ptr<binary_tree<T>> from_vector(const std::vector<T>& values) {
        auto tree = std::make_unique<binary_tree<T>>();
        for (const auto& v : values) {
            tree->insert(v);
        }
        return tree;
    }

    bool has_value() const { return has_value_; }

private:
    T value_{};
    bool has_value_ = false;
    ptr_type left_{};
    ptr_type right_{};
};

template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& values) {
    return binary_tree<T>::from_vector(values);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
