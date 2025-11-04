#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <utility>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_(data) {}
    explicit binary_tree(T&& data) : data_(std::move(data)) {}

    const T& data() const noexcept { return data_; }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(value));
            }
        }
    }

    void insert(T&& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(std::move(value));
            } else {
                left_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(std::move(value)));
            }
        } else {
            if (right_) {
                right_->insert(std::move(value));
            } else {
                right_ = std::unique_ptr<binary_tree<T>>(new binary_tree<T>(std::move(value)));
            }
        }
    }

    bool contains(const T& value) const noexcept {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    template <typename Func>
    void each(Func func) const {
        if (left_) {
            left_->each(func);
        }
        func(data_);
        if (right_) {
            right_->each(func);
        }
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
