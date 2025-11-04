#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <utility>
#include <cstddef>

namespace binary_search_tree {

template <typename T>
class binary_tree {
 public:
  explicit binary_tree(const T& value) : value_(value) {}
  explicit binary_tree(T&& value) : value_(std::move(value)) {}
  ~binary_tree() = default;

  // Insert a value into the tree. Values equal to a node go to the left subtree.
  void insert(const T& v) {
    if (v <= value_) {
      if (left_) {
        left_->insert(v);
      } else {
        left_ = std::unique_ptr<binary_tree>(new binary_tree(v));
      }
    } else {
      if (right_) {
        right_->insert(v);
      } else {
        right_ = std::unique_ptr<binary_tree>(new binary_tree(v));
      }
    }
  }

  const T& data() const { return value_; }

  const std::unique_ptr<binary_tree>& left() const { return left_; }
  const std::unique_ptr<binary_tree>& right() const { return right_; }

  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    iterator() : current_(nullptr) {}
    explicit iterator(const binary_tree* root) : current_(nullptr) {
      push_left(root);
      advance_();
    }

    reference operator*() const { return current_->value_; }
    pointer operator->() const { return &current_->value_; }

    iterator& operator++() {
      advance_();
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      advance_();
      return tmp;
    }

    bool operator==(const iterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) const {
      return current_ != other.current_;
    }

   private:
    const binary_tree* current_;
    std::vector<const binary_tree*> stack_;

    void push_left(const binary_tree* node) {
      while (node) {
        stack_.push_back(node);
        node = node->left_.get();
      }
    }

    void advance_() {
      if (stack_.empty()) {
        current_ = nullptr;
        return;
      }
      const binary_tree* node = stack_.back();
      stack_.pop_back();
      current_ = node;
      push_left(node->right_.get());
    }
  };

  iterator begin() { return iterator(this); }
  iterator end() { return iterator(); }
  iterator begin() const { return iterator(this); }
  iterator end() const { return iterator(); }

  binary_tree(const binary_tree&) = delete;
  binary_tree& operator=(const binary_tree&) = delete;
  binary_tree(binary_tree&&) noexcept = default;
  binary_tree& operator=(binary_tree&&) noexcept = default;

 private:
  T value_;
  std::unique_ptr<binary_tree> left_{};
  std::unique_ptr<binary_tree> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
