#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree final {
public:
    using value_type = T;

    binary_tree() noexcept = default;
    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) = default;
    binary_tree& operator=(binary_tree&&) = default;
    ~binary_tree() = default;

    void insert(const T& v) {
        if ((!has_value_)) {
            value_ = v;
            has_value_ = true;
        } else {
            if ((v <= value_)) {
                if ((left_ == nullptr)) {
                    left_ = std::make_unique<binary_tree<T>>();
                } else {
                    // no-op
                }
                left_->insert(v);
            } else {
                if ((right_ == nullptr)) {
                    right_ = std::make_unique<binary_tree<T>>();
                } else {
                    // no-op
                }
                right_->insert(v);
            }
        }
    }

    bool contains(const T& v) const noexcept {
        if ((!has_value_)) {
            return false;
        } else {
            if ((v == value_)) {
                return true;
            } else {
                if ((v < value_)) {
                    if ((left_ != nullptr)) {
                        return left_->contains(v);
                    } else {
                        return false;
                    }
                } else {
                    if ((right_ != nullptr)) {
                        return right_->contains(v);
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    const value_type& data() const noexcept {
        return value_;
    }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept {
        return left_;
    }

    const std::unique_ptr<binary_tree<T>>& right() const noexcept {
        return right_;
    }

    class const_iterator {
    public:
        const_iterator() noexcept = default;

        explicit const_iterator(const binary_tree<T>* root) noexcept {
            push_left(root);
        }

        const T& operator*() const {
            return stack_.back()->value_;
        }

        const_iterator& operator++() {
            const binary_tree<T>* node = stack_.back();
            stack_.pop_back();
            push_left(node->right_.get());
            return *this;
        }

        bool operator==(const const_iterator& other) const noexcept {
            if ((stack_.empty()) && (other.stack_.empty())) {
                return true;
            } else {
                if ((stack_.empty()) || (other.stack_.empty())) {
                    return false;
                } else {
                    return (stack_.back() == other.stack_.back());
                }
            }
        }

        bool operator!=(const const_iterator& other) const noexcept {
            return !(operator==(other));
        }

    private:
        void push_left(const binary_tree<T>* node) {
            const binary_tree<T>* current = node;
            while ((current != nullptr) && (current->has_value_)) {
                stack_.push_back(current);
                current = current->left_.get();
            }
        }

        std::vector<const binary_tree<T>*> stack_{};
    };

    const_iterator begin() const noexcept {
        if ((!has_value_)) {
            return end();
        } else {
            return const_iterator(this);
        }
    }

    const_iterator end() const noexcept {
        return const_iterator();
    }

private:
    bool has_value_{false};
    T value_{};
    std::unique_ptr<binary_tree<T>> left_{nullptr};
    std::unique_ptr<binary_tree<T>> right_{nullptr};
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
