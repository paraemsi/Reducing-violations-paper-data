#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>
#include <cstddef>
#include <iterator>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    using value_type = T;
    using node_ptr = std::unique_ptr<binary_tree<T>>;

    explicit binary_tree(const T& v) : value_(v), left_(nullptr), right_(nullptr) {}
    explicit binary_tree(T&& v) : value_(std::move(v)), left_(nullptr), right_(nullptr) {}

    const T& data() const noexcept {
        return value_;
    }

    void insert(const T& v) {
        binary_tree<T>* current = this;
        for (;;) {
            if ((v <= current->value_)) {
                if ((current->left_ == nullptr)) {
                    current->left_ = std::make_unique<binary_tree<T>>(v);
                    return;
                } else {
                    current = current->left_.get();
                }
            } else {
                if ((current->right_ == nullptr)) {
                    current->right_ = std::make_unique<binary_tree<T>>(v);
                    return;
                } else {
                    current = current->right_.get();
                }
            }
        }
    }

    void insert(T&& v) {
        binary_tree<T>* current = this;
        for (;;) {
            if ((v <= current->value_)) {
                if ((current->left_ == nullptr)) {
                    current->left_ = std::make_unique<binary_tree<T>>(std::move(v));
                    return;
                } else {
                    current = current->left_.get();
                }
            } else {
                if ((current->right_ == nullptr)) {
                    current->right_ = std::make_unique<binary_tree<T>>(std::move(v));
                    return;
                } else {
                    current = current->right_.get();
                }
            }
        }
    }

    const node_ptr& left() const noexcept {
        return left_;
    }

    const node_ptr& right() const noexcept {
        return right_;
    }

    class const_iterator {
    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        const_iterator() = default;

        explicit const_iterator(const binary_tree<T>* root) {
            push_left(root);
        }

        reference operator*() const {
            return stack_.back()->value_;
        }

        pointer operator->() const {
            return &(stack_.back()->value_);
        }

        const_iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if ((node->right_ != nullptr)) {
                push_left(node->right_.get());
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const noexcept {
            if ((stack_.empty()) && (other.stack_.empty())) {
                return true;
            }
            if ((stack_.empty()) || (other.stack_.empty())) {
                return false;
            }
            return (stack_.back() == other.stack_.back());
        }

        bool operator!=(const const_iterator& other) const noexcept {
            return (!(*this == other));
        }

    private:
        std::vector<const binary_tree<T>*> stack_{};

        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* current = node;
            while ((current != nullptr)) {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }
    };

    const_iterator begin() const noexcept {
        return const_iterator(this);
    }

    const_iterator end() const noexcept {
        return const_iterator();
    }

private:
    T value_;
    node_ptr left_;
    node_ptr right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
