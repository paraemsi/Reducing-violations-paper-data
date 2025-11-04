#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stack>
#include <initializer_list>

namespace binary_search_tree {

class BinarySearchTree {
 private:
  struct Node {
    int data;
    Node* left;
    Node* right;
    explicit Node(int d) : data(d), left(nullptr), right(nullptr) {}
  };

  Node* root_;

  static void insert(Node*& node, int value);
  static bool contains(const Node* node, int value);
  static void destroy(Node* node);

 public:
  BinarySearchTree() : root_(nullptr) {}
  ~BinarySearchTree();

  // Disable copy semantics to avoid accidental copying and double-free
  BinarySearchTree(const BinarySearchTree&) = delete;
  BinarySearchTree& operator=(const BinarySearchTree&) = delete;

  void insert(int value);
  bool contains(int value) const;
};

/*
 * Generic binary search tree used by the unit-tests.
 * Implemented entirely in-header because it is a template.
 */
template <class T>
class binary_tree {
  struct node {
    T data;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;

    explicit node(const T &value) : data(value) {}
  };

  std::unique_ptr<node> owned_;
  node* n_;

  /* Helper recursive insert */
  static void insert(std::unique_ptr<node> &n, const T &value) {
    if (!n) {
      n = std::make_unique<node>(value);
    } else if (value <= n->data) {
      insert(n->left, value);
    } else {
      insert(n->right, value);
    }
  }

 public:
  explicit binary_tree(const T &value) {
    owned_ = std::make_unique<node>(value);
    n_ = owned_.get();
  }

  /* Public insertion */
  void insert(const T &value) { insert(owned_, value); }

  // Internal constructor used for subtree wrappers (non-owning)
  explicit binary_tree(node* raw) : n_(raw) {}

  /* Accessors matching the tests’ expectations */
  const T &data() const { return n_->data; }
  const binary_tree *left() const {
    if (!n_->left) {
      return nullptr;
    }
    return new binary_tree(n_->left.get());
  }
  const binary_tree *right() const {
    if (!n_->right) {
      return nullptr;
    }
    return new binary_tree(n_->right.get());
  }

  /* Forward iterator performing an in-order traversal */
  class iterator {
    using node_ptr = const node *;
    std::stack<node_ptr> stack_;

    void push_left(node_ptr n) {
      while (n) {
        stack_.push(n);
        n = n->left.get();
      }
    }

   public:
    iterator() = default;
    explicit iterator(node_ptr root) { push_left(root); }

    const T &operator*() const { return stack_.top()->data; }

    iterator &operator++() {
      node_ptr cur = stack_.top();
      stack_.pop();
      push_left(cur->right.get());
      return *this;
    }

    bool operator==(const iterator &other) const {
      if (stack_.empty() && other.stack_.empty()) {
        return true;
      }
      if (!stack_.empty() && !other.stack_.empty()) {
        return stack_.top() == other.stack_.top();
      }
      return false;
    }
    bool operator!=(const iterator &other) const { return !(*this == other); }
  };

  iterator begin() const { return iterator(n_); }
  iterator end() const { return iterator(); }
};

/* Convenience helper used by unit-tests to build a tree from an initializer-list */
template <class T>
std::unique_ptr<binary_tree<T>> make_tree(std::initializer_list<T> values) {
  std::unique_ptr<binary_tree<T>> result;
  for (const auto &v : values) {
    if (!result) {
      result = std::make_unique<binary_tree<T>>(v);
    } else {
      result->insert(v);
    }
  }
  return result;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
