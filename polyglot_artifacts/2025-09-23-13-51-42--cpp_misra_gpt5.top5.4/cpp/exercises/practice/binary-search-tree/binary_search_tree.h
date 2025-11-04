#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    using node_type = binary_tree<T>;
    using node_ptr = std::unique_ptr<node_type>;

    explicit binary_tree(const T& v) : data_(v), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const T& value) {
        node_type* current = this;
        for (;;) {
            if ((value <= current->data_)) {
                if (current->left_ != nullptr) {
                    current = current->left_.get();
                } else {
                    current->left_ = node_ptr(new node_type(value));
                    return;
                }
            } else {
                if (current->right_ != nullptr) {
                    current = current->right_.get();
                } else {
                    current->right_ = node_ptr(new node_type(value));
                    return;
                }
            }
        }
    }

    const T& data() const noexcept {
        return data_;
    }

    const node_ptr& left() const noexcept {
        return left_;
    }

    const node_ptr& right() const noexcept {
        return right_;
    }

    class const_iterator {
    public:
        const_iterator() noexcept : current_(nullptr), stack_() {}

        explicit const_iterator(const node_type* root) noexcept : current_(nullptr), stack_() {
            descend_left(root);
            refresh_current();
        }

        const T& operator*() const {
            return current_->data_;
        }

        const_iterator& operator++() {
            if (current_ != nullptr) {
                const node_type* node = current_;
                stack_.pop_back();
                if (node->right_ != nullptr) {
                    descend_left(node->right_.get());
                } else {
                    // no-op
                }
                refresh_current();
            } else {
                // no-op
            }
            return *this;
        }

        bool operator==(const const_iterator& other) const noexcept {
            return (current_ == other.current_);
        }

        bool operator!=(const const_iterator& other) const noexcept {
            return (current_ != other.current_);
        }

    private:
        const node_type* current_;
        std::vector<const node_type*> stack_;

        void descend_left(const node_type* node) {
            const node_type* it = node;
            while (it != nullptr) {
                stack_.push_back(it);
                it = it->left_.get();
            }
        }

        void refresh_current() {
            if (stack_.empty()) {
                current_ = nullptr;
            } else {
                current_ = stack_.back();
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
    T data_;
    node_ptr left_;
    node_ptr right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
