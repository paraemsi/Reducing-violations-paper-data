#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stack>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data);                  // construct with initial data
    const T& data() const;                                // value stored at this node

    binary_tree* left();                                  // left-child accessor
    const binary_tree* left() const;
    binary_tree* right();                                 // right-child accessor
    const binary_tree* right() const;

    void insert(const T& value);                          // insert value, maintaining BST rules
    bool contains(const T& value) const;                  // true if value exists in the tree

    // in-order iterator support
    class iterator;
    iterator begin();              // non-const overload
    iterator begin() const;
    iterator end();                // non-const overload
    iterator end()   const;

    // copy / move support
    binary_tree(const binary_tree& other);                // deep-copy constructor
    binary_tree(binary_tree&& other) noexcept;            // move constructor
    binary_tree& operator=(const binary_tree& other);     // deep-copy assignment
    binary_tree& operator=(binary_tree&& other) noexcept; // move assignment

    ~binary_tree() = default;

private:
    T data_{};
    std::unique_ptr<binary_tree> left_{nullptr};
    std::unique_ptr<binary_tree> right_{nullptr};
};

// iterator definition
template <typename T>
class binary_tree<T>::iterator {
public:
    using value_type        = T;
    using reference         = const T&;
    using pointer           = const T*;
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    iterator() = default;
    explicit iterator(const binary_tree* root) { push_left(root); }

    reference operator*()  const { return stack_.top()->data_; }
    pointer   operator->() const { return &(stack_.top()->data_); }

    iterator& operator++() {
        const binary_tree* node = stack_.top();
        stack_.pop();
        if (node->right_) {
            push_left(node->right_.get());
        }
        return *this;
    }
    iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

    bool operator==(const iterator& other) const {
        if (stack_.empty() && other.stack_.empty())
            return true;
        if (stack_.empty() || other.stack_.empty())
            return false;
        return stack_.top() == other.stack_.top();
    }
    bool operator!=(const iterator& other) const { return !(*this == other); }

private:
    std::stack<const binary_tree*> stack_;
    void push_left(const binary_tree* node) {
        while (node) {
            stack_.push(node);
            node = node->left_.get();
        }
    }
};

// ---------- binary_tree implementation ----------

template <typename T>
binary_tree<T>::binary_tree(const T& data) : data_{data} {}

template <typename T>
const T& binary_tree<T>::data() const { return data_; }

template <typename T>
binary_tree<T>* binary_tree<T>::left() { return left_.get(); }

template <typename T>
const binary_tree<T>* binary_tree<T>::left() const { return left_.get(); }

template <typename T>
binary_tree<T>* binary_tree<T>::right() { return right_.get(); }

template <typename T>
const binary_tree<T>* binary_tree<T>::right() const { return right_.get(); }

template <typename T>
void binary_tree<T>::insert(const T& value) {
    if (value <= data_) {
        if (left_)
            left_->insert(value);
        else
            left_ = std::make_unique<binary_tree>(value);
    } else {
        if (right_)
            right_->insert(value);
        else
            right_ = std::make_unique<binary_tree>(value);
    }
}

template <typename T>
bool binary_tree<T>::contains(const T& value) const {
    if (value == data_)
        return true;
    if (value < data_)
        return left_ ? left_->contains(value) : false;
    return right_ ? right_->contains(value) : false;
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::begin() {
    return iterator(this);
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::begin() const {
    return iterator(this);
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::end() {
    return iterator();
}

template <typename T>
typename binary_tree<T>::iterator binary_tree<T>::end() const {
    return iterator();
}


// deep copy
template <typename T>
binary_tree<T>::binary_tree(const binary_tree& other) : data_{other.data_} {
    if (other.left_)
        left_ = std::make_unique<binary_tree>(*other.left_);
    if (other.right_)
        right_ = std::make_unique<binary_tree>(*other.right_);
}

template <typename T>
binary_tree<T>::binary_tree(binary_tree&& other) noexcept
    : data_{std::move(other.data_)},
      left_{std::move(other.left_)},
      right_{std::move(other.right_)} {}

template <typename T>
binary_tree<T>& binary_tree<T>::operator=(const binary_tree& other) {
    if (this == &other)
        return *this;
    left_.reset();
    right_.reset();
    data_ = other.data_;
    if (other.left_)
        left_ = std::make_unique<binary_tree>(*other.left_);
    if (other.right_)
        right_ = std::make_unique<binary_tree>(*other.right_);
    return *this;
}

template <typename T>
binary_tree<T>& binary_tree<T>::operator=(binary_tree&& other) noexcept {
    if (this == &other)
        return *this;
    data_  = std::move(other.data_);
    left_  = std::move(other.left_);
    right_ = std::move(other.right_);
    return *this;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
