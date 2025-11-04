#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <cstddef>  // for size_t

namespace binary_search_tree {

template <typename T>
class binary_tree {
private:
    T data_;
    std::unique_ptr<binary_tree> left_;
    std::unique_ptr<binary_tree> right_;
    
    void collect_inorder(std::vector<T>& result) const {
        if (left_) {
            left_->collect_inorder(result);
        }
        result.push_back(data_);
        if (right_) {
            right_->collect_inorder(result);
        }
    }
    
public:
    explicit binary_tree(const T& value) : data_(value), left_(nullptr), right_(nullptr) {}
    
    void insert(const T& value) {
        if (value <= data_) {
            if (left_) {
                left_->insert(value);
            } else {
                left_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            }
        } else {
            if (right_) {
                right_->insert(value);
            } else {
                right_ = std::unique_ptr<binary_tree>(new binary_tree(value));
            }
        }
    }
    
    const T& data() const {
        return data_;
    }
    
    const std::unique_ptr<binary_tree>& left() const {
        return left_;
    }
    
    const std::unique_ptr<binary_tree>& right() const {
        return right_;
    }
    
    // Iterator support for range-based for loop
    class iterator {
    private:
        std::vector<T> values;
        std::size_t index;
        
    public:
        iterator(const binary_tree* tree, bool is_end) : index(0) {
            if (!is_end && tree) {
                tree->collect_inorder(values);
            } else if (is_end && tree) {
                tree->collect_inorder(values);
                index = values.size();
            }
        }
        
        const T& operator*() const {
            return values[index];
        }
        
        iterator& operator++() {
            ++index;
            return *this;
        }
        
        bool operator!=(const iterator& other) const {
            return index != other.index || values.size() != other.values.size();
        }
    };
    
    iterator begin() const {
        return iterator(this, false);
    }
    
    iterator end() const {
        return iterator(this, true);
    }
};

}  // namespace binary_search_tree

#endif // BINARY_SEARCH_TREE_H
