#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <cstdint>
#include <string>

namespace binary_search_tree {

template <typename T>
class binary_tree {
public:
    binary_tree() : data_{} {}
    explicit binary_tree(T value) : data_(value) {}
    
    void insert(T value);
    bool find(T value) const;
    
    // Add the required interface
    const T& data() const { 
        return data_;
    }
    const binary_tree* left() const { 
        if (left_) {
            return left_.get();
        }
        return nullptr;
    }
    const binary_tree* right() const { 
        if (right_) {
            return right_.get();
        }
        return nullptr;
    }
    
private:
    T data_{};
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
