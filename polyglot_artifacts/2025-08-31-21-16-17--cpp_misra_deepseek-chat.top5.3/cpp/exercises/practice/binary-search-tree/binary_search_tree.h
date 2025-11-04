#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <memory>
#include <string>

namespace binary_search_tree {

template<typename T>
class binary_tree {
public:
    explicit binary_tree(T data);
    
    const T& data() const;
    const binary_tree<T>* left() const;
    const binary_tree<T>* right() const;
    
    void insert(T data);
    
private:
    T data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
