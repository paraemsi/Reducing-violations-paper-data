#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_(data) {}

    const T& data() const noexcept { return data_; }

    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    std::unique_ptr<binary_tree<T>>& left() noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }
    std::unique_ptr<binary_tree<T>>& right() noexcept { return right_; }

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
        cached_ = false;
    }

    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const {
        ensure_cache();
        return cache_.begin();
    }

    const_iterator end() const {
        ensure_cache();
        return cache_.end();
    }

    const_iterator cbegin() const {
        ensure_cache();
        return cache_.cbegin();
    }

    const_iterator cend() const {
        ensure_cache();
        return cache_.cend();
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_{};
    std::unique_ptr<binary_tree<T>> right_{};

    mutable std::vector<T> cache_;
    mutable bool cached_ = false;

    void inorder_fill(std::vector<T>& out) const {
        if (left_) {
            left_->inorder_fill(out);
        }
        out.push_back(data_);
        if (right_) {
            right_->inorder_fill(out);
        }
    }

    void ensure_cache() const {
        if (!cached_) {
            cache_.clear();
            inorder_fill(cache_);
            cached_ = true;
        }
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
