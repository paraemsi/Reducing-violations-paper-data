#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>

namespace binary_search_tree {

class binary_tree {
public:
    binary_tree() : data_(), left_(nullptr), right_(nullptr) {}
    
    explicit binary_tree(std::int32_t data) : data_(data), left_(nullptr), right_(nullptr) {}
    
    void insert(std::int32_t value);
    bool contains(std::int32_t value) const;
    
    std::int32_t data() const {
        return data_;
    }
    
    const binary_tree* left() const {
        return left_.get();
    }
    
    const binary_tree* right() const {
        return right_.get();
    }

private:
    std::int32_t data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
