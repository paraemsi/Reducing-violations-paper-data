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
    using node_ptr = std::unique_ptr<binary_tree<value_type>>;
    using container_type = std::vector<value_type>;
    using const_iterator = typename container_type::const_iterator;

    explicit binary_tree(const value_type& v)
        : data_(v), left_(nullptr), right_(nullptr), ordered_(), cache_valid_(false)
    {
    }

    binary_tree(const binary_tree&) = delete;
    binary_tree& operator=(const binary_tree&) = delete;
    binary_tree(binary_tree&&) noexcept = default;
    binary_tree& operator=(binary_tree&&) noexcept = default;
    ~binary_tree() = default;

    void insert(const value_type& v)
    {
        if ((v <= data_)) {
            if (!left_) {
                left_.reset(new binary_tree<value_type>(v));
            } else {
                left_->insert(v);
            }
        } else {
            if (!right_) {
                right_.reset(new binary_tree<value_type>(v));
            } else {
                right_->insert(v);
            }
        }
        cache_valid_ = false;
    }

    const value_type& data() const noexcept
    {
        return data_;
    }

    node_ptr& left() noexcept
    {
        return left_;
    }
    const node_ptr& left() const noexcept
    {
        return left_;
    }

    node_ptr& right() noexcept
    {
        return right_;
    }
    const node_ptr& right() const noexcept
    {
        return right_;
    }

    const_iterator begin() const
    {
        refresh_cache();
        return ordered_.cbegin();
    }

    const_iterator end() const
    {
        refresh_cache();
        return ordered_.cend();
    }

private:
    void inorder_fill(const binary_tree<value_type>* node, container_type& out) const
    {
        if (node == nullptr) {
            return;
        } else {
            inorder_fill(node->left_.get(), out);
            out.push_back(node->data_);
            inorder_fill(node->right_.get(), out);
        }
    }

    void refresh_cache() const
    {
        if ((!cache_valid_)) {
            ordered_.clear();
            inorder_fill(this, ordered_);
            cache_valid_ = true;
        }
    }

    value_type data_;
    node_ptr left_;
    node_ptr right_;
    mutable container_type ordered_;
    mutable bool cache_valid_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
