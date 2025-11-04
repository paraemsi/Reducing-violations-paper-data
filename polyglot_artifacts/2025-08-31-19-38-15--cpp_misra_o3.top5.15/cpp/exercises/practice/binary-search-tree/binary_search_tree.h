#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>

namespace binary_search_tree {

template<typename T>
class binary_tree final
{
public:
    binary_tree() noexcept : has_value(false), data_{}, leftChild(nullptr), rightChild(nullptr) {}

    void insert(const T& value)
    {
        if (!has_value)
        {
            data_ = value;
            has_value = true;
            return;
        }

        if (value <= data_)
        {
            if (leftChild == nullptr)
            {
                leftChild = std::make_unique<binary_tree<T>>();
            }
            leftChild->insert(value);
        }
        else
        {
            if (rightChild == nullptr)
            {
                rightChild = std::make_unique<binary_tree<T>>();
            }
            rightChild->insert(value);
        }
    }

    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        if (!has_value)
        {
            return false;
        }

        if (value == data_)
        {
            return true;
        }

        if (value < data_)
        {
            return (leftChild != nullptr) && leftChild->contains(value);
        }
        return (rightChild != nullptr) && rightChild->contains(value);
    }

    [[nodiscard]] const T& data() const noexcept
    {
        return data_;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& left() const noexcept
    {
        return leftChild;
    }

    [[nodiscard]] const std::unique_ptr<binary_tree<T>>& right() const noexcept
    {
        return rightChild;
    }

    class iterator
    {
    public:
        using value_type = T;
        using reference  = const T&;
        using pointer    = const T*;
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator() noexcept = default;
        explicit iterator(const binary_tree<T>* root)
        {
            pushLeft(root);
        }

        reference operator*() const noexcept
        {
            return nodes.back()->data_;
        }

        pointer operator->() const noexcept
        {
            return &(nodes.back()->data_);
        }

        iterator& operator++()
        {
            const binary_tree<T>* node = nodes.back();
            nodes.pop_back();
            if (node->rightChild != nullptr)
            {
                pushLeft(node->rightChild.get());
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp(*this);
            static_cast<void>(++(*this));
            return temp;
        }

        friend bool operator==(const iterator& a, const iterator& b) noexcept
        {
            return a.nodes == b.nodes;
        }

        friend bool operator!=(const iterator& a, const iterator& b) noexcept
        {
            return !(a == b);
        }

    private:
        std::vector<const binary_tree<T>*> nodes;

        void pushLeft(const binary_tree<T>* node)
        {
            const binary_tree<T>* current = node;
            while ((current != nullptr) && current->has_value)
            {
                nodes.push_back(current);
                current = (current->leftChild != nullptr) ? current->leftChild.get() : nullptr;
            }
        }
    };

    iterator begin() const
    {
        return iterator(this);
    }

    iterator end() const noexcept
    {
        return iterator();
    }

private:
    bool has_value;
    T data_;
    std::unique_ptr<binary_tree<T>> leftChild;
    std::unique_ptr<binary_tree<T>> rightChild;
};

class BinarySearchTree final
{
public:
    BinarySearchTree() noexcept;
    explicit BinarySearchTree(std::int32_t rootValue);
    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree(BinarySearchTree&& other) noexcept = delete;
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept = delete;
    ~BinarySearchTree() noexcept;

    void insert(std::int32_t value);
    [[nodiscard]] bool contains(std::int32_t value) const;

private:
    struct Node
    {
        explicit Node(std::int32_t val) noexcept : value(val), leftChild(nullptr), rightChild(nullptr) {}

        std::int32_t value;
        Node* leftChild;
        Node* rightChild;
    };

    Node* root;

    static void destroySubTree(Node* node) noexcept;
    static void insertNode(Node*& node, std::int32_t value);
    static bool containsNode(const Node* node, std::int32_t value) noexcept;
};

}  // namespace binary_search_tree

#endif  // BINARY_SEARCH_TREE_H
