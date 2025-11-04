#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& value)
        : data_{value}, left_{}, right_{} {}

    void insert(const T& value)
    {
        if ((value <= data_)) {
            if ((left_ == nullptr)) {
                left_ = std::make_unique<binary_tree<T>>(value);
            } else {
                left_->insert(value);
            }
        } else {
            if ((right_ == nullptr)) {
                right_ = std::make_unique<binary_tree<T>>(value);
            } else {
                right_->insert(value);
            }
        }
    }

    bool contains(const T& value) const
    {
        if ((value == data_)) {
            return true;
        } else if ((value < data_)) {
            if ((left_ != nullptr)) {
                return left_->contains(value);
            } else {
                return false;
            }
        } else {
            if ((right_ != nullptr)) {
                return right_->contains(value);
            } else {
                return false;
            }
        }
    }

    const T& data() const noexcept
    {
        return data_;
    }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return left_;
    }

    const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return right_;
    }

    class iterator {
    public:
        using self_type = iterator;

        iterator() noexcept
            : current_{nullptr}, stack_{} {}

        explicit iterator(const binary_tree<T>* root)
            : current_{nullptr}, stack_{} {
            push_left(root);
        }

        const T& operator*() const
        {
            return current_->data_;
        }

        self_type& operator++()
        {
            if ((current_ == nullptr)) {
                return *this;
            }

            const binary_tree<T>* node = current_;
            if ((!stack_.empty())) {
                stack_.pop_back();
            }

            if ((node->right_.get() != nullptr)) {
                push_left(node->right_.get());
            } else {
                if ((!stack_.empty())) {
                    current_ = stack_.back();
                } else {
                    current_ = nullptr;
                }
            }
            return *this;
        }

        bool operator!=(const self_type& other) const noexcept
        {
            return (current_ != other.current_);
        }

        bool operator==(const self_type& other) const noexcept
        {
            return (current_ == other.current_);
        }

    private:
        void push_left(const binary_tree<T>* node)
        {
            const binary_tree<T>* it = node;
            while ((it != nullptr)) {
                stack_.push_back(it);
                it = it->left_.get();
            }
            if ((!stack_.empty())) {
                current_ = stack_.back();
            } else {
                current_ = nullptr;
            }
        }

        const binary_tree<T>* current_;
        std::vector<const binary_tree<T>*> stack_;
    };

    iterator begin() noexcept
    {
        return iterator(this);
    }

    iterator end() noexcept
    {
        return iterator();
    }

    iterator begin() const noexcept
    {
        return iterator(this);
    }

    iterator end() const noexcept
    {
        return iterator();
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
