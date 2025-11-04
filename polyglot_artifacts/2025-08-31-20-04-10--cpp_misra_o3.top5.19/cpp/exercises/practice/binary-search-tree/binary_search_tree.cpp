#include "binary_search_tree.h"

#include <memory>

namespace binary_search_tree {

BinarySearchTree::BinarySearchTree() noexcept :
    m_is_initialized(false),
    m_data(static_cast<std::int32_t>(0)),
    m_left(nullptr),
    m_right(nullptr)
{
}

BinarySearchTree::BinarySearchTree(std::int32_t data) noexcept :
    m_is_initialized(true),
    m_data(data),
    m_left(nullptr),
    m_right(nullptr)
{
}

void BinarySearchTree::insert(std::int32_t value)
{
    if (!m_is_initialized)
    {
        m_data = value;
        m_is_initialized = true;
        return;
    }

    if (value <= m_data)
    {
        insert_internal(m_left, value);
    }
    else
    {
        insert_internal(m_right, value);
    }
}

void BinarySearchTree::insert_internal(std::unique_ptr<BinarySearchTree>& subtree,
                                       std::int32_t value)
{
    if (subtree == nullptr)
    {
        subtree = std::make_unique<BinarySearchTree>(value);
    }
    else
    {
        if (value <= subtree->m_data)
        {
            insert_internal(subtree->m_left, value);
        }
        else
        {
            insert_internal(subtree->m_right, value);
        }
    }
}

bool BinarySearchTree::search(std::int32_t value) const noexcept
{
    if (!m_is_initialized)
    {
        return false;
    }
    return search_internal(this, value);
}

bool BinarySearchTree::search_internal(const BinarySearchTree* subtree,
                                       std::int32_t value) const noexcept
{
    if (subtree == nullptr)
    {
        return false;
    }

    if (value == subtree->m_data)
    {
        return true;
    }

    if (value < subtree->m_data)
    {
        return search_internal(subtree->m_left.get(), value);
    }
    else
    {
        return search_internal(subtree->m_right.get(), value);
    }
}

}  // namespace binary_search_tree
