#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H
#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    explicit binary_tree(const T& data) : data_{data} {}

    const T& data() const { return data_; }

    // Accessors return references to the owning unique_ptr so that tests can
    // receive the expected `const std::unique_ptr<binary_tree<T>>&` type.
    std::unique_ptr<binary_tree<T>>& left() { return left_; }
    const std::unique_ptr<binary_tree<T>>& left() const { return left_; }

    std::unique_ptr<binary_tree<T>>& right() { return right_; }
    const std::unique_ptr<binary_tree<T>>& right() const { return right_; }

    // Forward-in-order iteration support -----------------------------------
    using iterator = typename std::vector<T>::const_iterator;

    iterator begin() const {
        ensure_cache();
        return traversal_cache_.cbegin();
    }

    iterator end() const {
        ensure_cache();
        return traversal_cache_.cend();
    }

    void insert(const T& value) {
        // insertion changes the tree topology – invalidate cached traversal
        cache_valid_ = false;
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree<T>>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree<T>>(value);
            }
        }
    }

    std::vector<T> sorted_data() const {
        std::vector<T> result;
        if (left_) {
            auto left_vec = left_->sorted_data();
            result.insert(result.end(), left_vec.begin(), left_vec.end());
        }
        result.push_back(data_);
        if (right_) {
            auto right_vec = right_->sorted_data();
            result.insert(result.end(), right_vec.begin(), right_vec.end());
        }
        return result;
    }

private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    // ---- internal helpers used by iterator support ----
    void build_traversal(std::vector<T>& vec) const {
        if (left_) {
            left_->build_traversal(vec);
        }
        vec.push_back(data_);
        if (right_) {
            right_->build_traversal(vec);
        }
    }

    void ensure_cache() const {
        if (!cache_valid_) {
            traversal_cache_.clear();
            build_traversal(traversal_cache_);
            cache_valid_ = true;
        }
    }

    mutable std::vector<T> traversal_cache_;
    mutable bool cache_valid_ = false;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
