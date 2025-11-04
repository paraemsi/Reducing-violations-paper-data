#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    using value_type = T;

    explicit binary_tree(const T& v) : value_{v}, left_{nullptr}, right_{nullptr} {}
    explicit binary_tree(T&& v) : value_{std::move(v)}, left_{nullptr}, right_{nullptr} {}

    void insert(const T& v) {
        if ((v <= value_)) {
            if ((left_ == nullptr)) {
                left_ = std::make_unique<binary_tree>(v);
            } else {
                left_->insert(v);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::make_unique<binary_tree>(v);
            } else {
                right_->insert(v);
            }
        }
    }

    bool contains(const T& v) const noexcept {
        const binary_tree* current = this;
        while ((current != nullptr)) {
            if ((v == current->value_)) {
                return true;
            } else {
                if ((v <= current->value_)) {
                    current = current->left_.get();
                } else {
                    current = current->right_.get();
                }
            }
        }
        return false;
    }

    const T& data() const noexcept {
        return value_;
    }

    const std::unique_ptr<binary_tree>& left() const noexcept {
        return left_;
    }

    const std::unique_ptr<binary_tree>& right() const noexcept {
        return right_;
    }

    class iterator final {
    public:
        iterator() = default;
        explicit iterator(const binary_tree* root) {
            push_left(root);
        }

        const T& operator*() const {
            return stack_.back()->value_;
        }

        const T* operator->() const {
            return &(stack_.back()->value_);
        }

        iterator& operator++() {
            const binary_tree* node = stack_.back();
            stack_.pop_back();
            if ((node->right_.get() != nullptr)) {
                push_left(node->right_.get());
            }
            return (*this);
        }

        bool operator==(const iterator& other) const {
            if ((stack_.empty()) && (other.stack_.empty())) {
                return true;
            }
            if ((stack_.empty()) || (other.stack_.empty())) {
                return false;
            }
            return (stack_.back() == other.stack_.back());
        }

        bool operator!=(const iterator& other) const {
            return (!((*this) == other));
        }

    private:
        std::vector<const binary_tree*> stack_{};

        void push_left(const binary_tree* node) {
            const binary_tree* current = node;
            while ((current != nullptr)) {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }
    };

    iterator begin() const {
        return iterator(this);
    }

    iterator end() const noexcept {
        return iterator();
    }

private:
    T value_;
    std::unique_ptr<binary_tree> left_{};
    std::unique_ptr<binary_tree> right_{};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
