#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    // Add a default constructor
    binary_tree() = default;
    binary_tree(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    const T& data() const { return data_; }
    const binary_tree* left() const { return left_.get(); }
    const binary_tree* right() const { return right_.get(); }
    
    void insert(const T& value) {
        // If data_ hasn't been set yet (for an empty tree)
        if (!is_initialized_) {
            data_ = value;
            is_initialized_ = true;
            return;
        }
        
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::make_unique<binary_tree>(value);
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::make_unique<binary_tree>(value);
            }
        }
    }

private:
    T data_{};
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    bool is_initialized_ = false;
};

// Helper function to create a tree from a series of data
template <typename T>
std::unique_ptr<binary_tree<T>> make_tree(const std::vector<T>& data) {
    auto root = std::make_unique<binary_tree<T>>();
    for (const auto& value : data) {
        root->insert(value);
    }
    return root;
}

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
