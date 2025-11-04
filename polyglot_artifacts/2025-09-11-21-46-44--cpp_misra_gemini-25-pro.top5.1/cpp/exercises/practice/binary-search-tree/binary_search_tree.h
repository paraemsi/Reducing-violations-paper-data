#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <type_traits>
#include <utility>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;

    explicit binary_tree(const T& value);
    ~binary_tree();

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;

    binary_tree(binary_tree&& other) noexcept(std::is_nothrow_move_constructible<T>::value);
    binary_tree& operator=(binary_tree&& other) noexcept(std::is_nothrow_move_assignable<T>::value);

    void insert(const T& value);

    const binary_tree<T>* search(const T& value) const;

    const std::unique_ptr<binary_tree<T>>& left() const;
    const std::unique_ptr<binary_tree<T>>& right() const;
    const T& data() const;

private:
    value_type tree_data;
    std::unique_ptr<binary_tree<T>> left_tree;
    std::unique_ptr<binary_tree<T>> right_tree;
};

template <typename T>
binary_tree<T>::binary_tree(const T& value)
    : tree_data{value}, left_tree{nullptr}, right_tree{nullptr} {}

template <typename T>
binary_tree<T>::~binary_tree() = default;

template <typename T>
binary_tree<T>::binary_tree(binary_tree<T>&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
    : tree_data{std::move(other.tree_data)},
      left_tree{std::move(other.left_tree)},
      right_tree{std::move(other.right_tree)} {}

template <typename T>
binary_tree<T>& binary_tree<T>::operator=(binary_tree<T>&& other) noexcept(std::is_nothrow_move_assignable<T>::value) {
    if (this != &other) {
        tree_data = std::move(other.tree_data);
        left_tree = std::move(other.left_tree);
        right_tree = std::move(other.right_tree);
    }
    return *this;
}

template <typename T>
void binary_tree<T>::insert(const T& value) {
    if (value <= tree_data) {
        if (left_tree) {
            left_tree->insert(value);
        } else {
            left_tree = std::make_unique<binary_tree<T>>(value);
        }
    } else {
        if (right_tree) {
            right_tree->insert(value);
        } else {
            right_tree = std::make_unique<binary_tree<T>>(value);
        }
    }
}

template <typename T>
const binary_tree<T>* binary_tree<T>::search(const T& value) const {
    const binary_tree<T>* result{nullptr};

    if (value == tree_data) {
        result = this;
    } else if (value <= tree_data) {
        if (left_tree) {
            result = left_tree->search(value);
        }
    } else {
        if (right_tree) {
            result = right_tree->search(value);
        }
    }

    return result;
}

template <typename T>
const T& binary_tree<T>::data() const {
    return tree_data;
}

template <typename T>
const std::unique_ptr<binary_tree<T>>& binary_tree<T>::left() const {
    return left_tree;
}

template <typename T>
const std::unique_ptr<binary_tree<T>>& binary_tree<T>::right() const {
    return right_tree;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
