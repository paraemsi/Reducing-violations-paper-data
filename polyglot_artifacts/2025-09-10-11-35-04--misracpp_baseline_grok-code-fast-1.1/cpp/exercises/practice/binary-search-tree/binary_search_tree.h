#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <utility>
#include <vector>

namespace binary_search_tree {

template<typename T>
class binary_tree {
private:
    T value;
    std::unique_ptr<binary_tree<T>> left_child;
    std::unique_ptr<binary_tree<T>> right_child;

public:
    binary_tree(T val) : value(std::move(val)), left_child(nullptr), right_child(nullptr) {}

    const T& data() const { return value; }

    const std::unique_ptr<binary_tree<T>>& left() const { return left_child; }

    const std::unique_ptr<binary_tree<T>>& right() const { return right_child; }

    void insert(T val) {
        if (val <= value) {
            if (!left_child) {
                left_child = std::make_unique<binary_tree<T>>(std::move(val));
            } else {
                left_child->insert(std::move(val));
            }
        } else {
            if (!right_child) {
                right_child = std::make_unique<binary_tree<T>>(std::move(val));
            } else {
                right_child->insert(std::move(val));
            }
        }
    }

    class iterator {
    private:
        std::vector<const binary_tree<T>*> stack;
        void push_left(const binary_tree<T>* node) {
            while (node) {
                stack.push_back(node);
                node = node->left_child.get();
            }
        }
    public:
        iterator(const binary_tree<T>* root) {
            push_left(root);
        }
        iterator() = default;
        const T& operator*() const {
            return stack.back()->value;
        }
        iterator& operator++() {
            const binary_tree<T>* node = stack.back();
            stack.pop_back();
            if (node->right_child) {
                push_left(node->right_child.get());
            }
            return *this;
        }
        bool operator==(const iterator& other) const {
            return stack == other.stack;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    iterator begin() const {
        return iterator(this);
    }

    iterator end() const {
        return iterator();
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
