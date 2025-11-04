#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    binary_tree() : data_{}, left_(nullptr), right_(nullptr) {}
    explicit binary_tree(T value) : data_(value), left_(std::make_unique<binary_tree>()), right_(std::make_unique<binary_tree>()) {}
    
    void insert(T value);
    bool contains(T value) const;
    const T* data() const;
    const binary_tree* left() const;
    const binary_tree* right() const;
    
private:
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    
    void insert_impl(T value);
    bool contains_impl(T value) const;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
