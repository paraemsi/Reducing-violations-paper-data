#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <utility>

#if __cplusplus >= 201703L
#define BST_NODISCARD [[nodiscard]]
#else
#define BST_NODISCARD
#endif

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using tree_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& value) : value_(value) {}

    // Insert a new value into the binary search tree.
    void insert(const T& value) {
        if (value <= value_) {
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

    // Return true if the value exists in the tree.
    BST_NODISCARD bool contains(const T& value) const noexcept {
        if (value == value_) {
            return true;
        }
        if (value < value_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    // Accessors
    BST_NODISCARD const T& data() const noexcept { return value_; }
    BST_NODISCARD const tree_ptr& left() const noexcept { return left_; }
    BST_NODISCARD const tree_ptr& right() const noexcept { return right_; }

private:
    T value_;
    tree_ptr left_{};
    tree_ptr right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
