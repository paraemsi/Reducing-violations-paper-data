#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_{data} {}

    // Accessors
    const T& data() const noexcept { return data_; }
    const std::unique_ptr<binary_tree<T>>& left() const noexcept { return left_; }
    const std::unique_ptr<binary_tree<T>>& right() const noexcept { return right_; }

    // Operations
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

    bool contains(const T& value) const noexcept {
        if (value == data_) {
            return true;
        }
        if (value < data_) {
            return left_ ? left_->contains(value) : false;
        }
        return right_ ? right_->contains(value) : false;
    }

    std::vector<T> as_vector() const {
        std::vector<T> out;
        in_order_collect(out);
        return out;
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    void in_order_collect(std::vector<T>& out) const {
        if (left_) {
            left_->in_order_collect(out);
        }
        out.push_back(data_);
        if (right_) {
            right_->in_order_collect(out);
        }
    }
};

// Free function to search for a value in the tree
template <typename T>
inline bool search(const binary_tree<T>& tree, const T& value) noexcept {
    return tree.contains(value);
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
