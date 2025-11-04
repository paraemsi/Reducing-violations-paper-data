#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <stack>

namespace binary_search_tree {

template <typename T>
class binary_tree {
 public:
    explicit binary_tree(const T& data) : data_{data} {}

    ~binary_tree();
    void insert(const T& item);
    const binary_tree* search(const T& item) const;

    const std::unique_ptr<binary_tree>& left() const { return left_; }
    const std::unique_ptr<binary_tree>& right() const { return right_; }
    const T& data() const { return data_; }

    class tree_iterator {
     public:
        tree_iterator() : current_node_{nullptr} {}
        const T& operator*() const { return current_node_->data_; }

        tree_iterator& operator++() {
            path_.pop();
            if (current_node_->right_) {
                descend_left(current_node_->right_.get());
            }

            if (path_.empty()) {
                current_node_ = nullptr;
            } else {
                current_node_ = path_.top();
            }

            return *this;
        }

        bool operator!=(const tree_iterator& other) const {
            return current_node_ != other.current_node_;
        }

     private:
        friend class binary_tree;

        explicit tree_iterator(const binary_tree* root) {
            descend_left(root);
            if (!path_.empty()) {
                current_node_ = path_.top();
            }
        }

        void descend_left(const binary_tree* node) {
            while (node) {
                path_.push(node);
                node = node->left_.get();
            }
        }

        const binary_tree* current_node_{nullptr};
        std::stack<const binary_tree*> path_;
    };

    tree_iterator begin() const { return tree_iterator(this); }
    tree_iterator end() const { return tree_iterator(); }

 private:
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

template <typename T>
void binary_tree<T>::insert(const T& item) {
    auto current = this;
    while (true) {
        if (item < current->data_) {
            if (current->left_) {
                current = current->left_.get();
            } else {
                current->left_ = std::make_unique<binary_tree>(item);
                return;
            }
        } else if (item > current->data_) {
            if (current->right_) {
                current = current->right_.get();
            } else {
                current->right_ = std::make_unique<binary_tree>(item);
                return;
            }
        } else {
            // item is equal to current node's data, do nothing
            return;
        }
    }
}

template <typename T>
binary_tree<T>::~binary_tree() {
    std::stack<std::unique_ptr<binary_tree>> nodes;
    if (left_) {
        nodes.push(std::move(left_));
    }
    if (right_) {
        nodes.push(std::move(right_));
    }
    while (!nodes.empty()) {
        auto node = std::move(nodes.top());
        nodes.pop();
        if (node->left_) {
            nodes.push(std::move(node->left_));
        }
        if (node->right_) {
            nodes.push(std::move(node->right_));
        }
    }
}

template <typename T>
const binary_tree<T>* binary_tree<T>::search(const T& item) const {
    const binary_tree* current = this;
    while (current) {
        if (item < current->data_) {
            current = current->left_.get();
        } else if (item > current->data_) {
            current = current->right_.get();
        } else {
            return current;
        }
    }
    return nullptr;
}

}  // namespace binary_search_tree

#endif  // BINARY_SEARCH_TREE_H
