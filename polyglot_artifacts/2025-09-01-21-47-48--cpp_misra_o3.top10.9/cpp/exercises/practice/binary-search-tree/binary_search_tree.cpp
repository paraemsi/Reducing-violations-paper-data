#include "binary_search_tree.h"

#include <cstdint>
#include <memory>

namespace binary_search_tree {

struct BinarySearchTree::Node
{
    explicit Node(std::int32_t value_in) :
        data{value_in},
        left{nullptr},
        right{nullptr}
    {
    }

    void insert(std::int32_t value_in)
    {
        if(value_in <= data)
        {
            if(left == nullptr)
            {
                left = std::make_unique<Node>(value_in);
            }
            else
            {
                left->insert(value_in);
            }
        }
        else
        {
            if(right == nullptr)
            {
                right = std::make_unique<Node>(value_in);
            }
            else
            {
                right->insert(value_in);
            }
        }
    }

    bool contains(std::int32_t value_in) const
    {
        if(value_in == data)
        {
            return true;
        }
        else if(value_in < data)
        {
            if(left == nullptr)
            {
                return false;
            }
            else
            {
                return left->contains(value_in);
            }
        }
        else
        {
            if(right == nullptr)
            {
                return false;
            }
            else
            {
                return right->contains(value_in);
            }
        }
    }

    std::int32_t data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};  // struct Node

void BinarySearchTree::insert(std::int32_t value)
{
    if(root_ == nullptr)
    {
        root_ = std::make_unique<Node>(value);
    }
    else
    {
        root_->insert(value);
    }
}

bool BinarySearchTree::contains(std::int32_t value) const
{
    if(root_ == nullptr)
    {
        return false;
    }
    else
    {
        return root_->contains(value);
    }
}

BinarySearchTree::~BinarySearchTree() = default;

}  // namespace binary_search_tree
