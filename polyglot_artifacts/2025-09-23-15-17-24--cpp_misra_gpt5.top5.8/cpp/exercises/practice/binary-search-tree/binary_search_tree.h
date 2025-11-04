#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    using value_type = T;

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

public:
    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    const T& data() const noexcept {
        return data_;
    }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept {
        return left_;
    }

    const std::unique_ptr<binary_tree<T>>& right() const noexcept {
        return right_;
    }

    void insert(const T& v) {
        if ((v <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(v));
            } else {
                left_->insert(v);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(v));
            } else {
                right_->insert(v);
            }
        }
    }

    bool contains(const T& v) const noexcept {
        const binary_tree<T>* current = this;
        while ((current != nullptr)) {
            if ((v == current->data_)) {
                return true;
            } else {
                if ((v <= current->data_)) {
                    if ((current->left_ != nullptr)) {
                        current = current->left_.get();
                    } else {
                        current = nullptr;
                    }
                } else {
                    if ((current->right_ != nullptr)) {
                        current = current->right_.get();
                    } else {
                        current = nullptr;
                    }
                }
            }
        }
        return false;
    }

    class iterator {
    private:
        std::vector<binary_tree<T>*> stack_;

        void push_left(binary_tree<T>* node) {
            binary_tree<T>* n = node;
            while ((n != nullptr)) {
                stack_.push_back(n);
                if ((n->left_ != nullptr)) {
                    n = n->left_.get();
                } else {
                    n = nullptr;
                }
            }
        }

    public:
        iterator() = default;

        explicit iterator(binary_tree<T>* root) {
            push_left(root);
        }

        T& operator*() const {
            return stack_.back()->data_;
        }

        T* operator->() const {
            return &(stack_.back()->data_);
        }

        iterator& operator++() {
            binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            if ((node->right_ != nullptr)) {
                push_left(node->right_.get());
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            (void) ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return (stack_ == other.stack_);
        }

        bool operator!=(const iterator& other) const {
            return !(stack_ == other.stack_);
        }
    };

    class const_iterator {
    private:
        std::vector<const binary_tree<T>*> stack_;

        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* n = node;
            while ((n != nullptr)) {
                stack_.push_back(n);
                if ((n->left_ != nullptr)) {
                    n = n->left_.get();
                } else {
                    n = nullptr;
                }
            }
        }

    public:
        const_iterator() = default;

        explicit const_iterator(const binary_tree<T>* root) {
            push_left(root);
        }

        const T& operator*() const {
            return stack_.back()->data_;
        }

        const T* operator->() const {
            return &(stack_.back()->data_);
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
            (void) ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return (stack_ == other.stack_);
        }

        bool operator!=(const const_iterator& other) const {
            return !(stack_ == other.stack_);
        }
    };

    iterator begin() {
        return iterator(this);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const {
        return const_iterator(this);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
